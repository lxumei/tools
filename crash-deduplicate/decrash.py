#!/usr/bin/env python3
import os
import re
import sys
import time
import getopt

hang_file = '/tmp/.hang'
crash_file = 'uniq-crash'
log_file = 'crash-log'
uniq_crash_hash = []
stack_trace_number = 5

#./decrash.py -c crash_dir -t path/to/target args/of/target
def usage():
    print("usage:")
    print(" ./decrash.py -c crash_dir -t path/to/target args/of/target")
    sys.exit(0)

def input_parser():
    options, args = getopt.getopt(sys.argv[1:], "hi:t:", ["help", "in=", "target="])
    if(len(options) <= 0):
        usage()

    for name, value in options:
        if name in ("-h", "--help"):
            usage()
        elif name in ("-i", "--in"):
            crash_dir = os.path.abspath(value)
            if(not os.path.exists(crash_dir)):
                print("{} not exists!".format(value))
                sys.exit(0)
        elif name in ("-t", "--target"):
            target_path = os.path.abspath(value)

    target_args = ''.join(args)
    return crash_dir, target_path, target_args


def uniq_crash_determine():
    lines = open(log_file, 'r').readlines()
    new_lines =[]
    for i in range(0, len(lines)):
        if(lines[i][0] == '#'):
            new_lines.append(lines[i])
        else:
            new_lines[-1] = new_lines[-1].strip('\n') + lines[i]
    
    stack_number = 0
    res = addr = fun = source = lnumber = ''
    for line in new_lines:
        if(stack_number > stack_trace_number):
            break;
        line = re.sub(r'\(.*\)', '', line)
        addr = re.findall(r'(0x.+) in', line)
        if addr == []:
            addr = 'NULL'
            fun = re.findall(r'#\d+ +([^ ]+) +', line)
        else:
            addr = addr[0]
            fun = re.findall(r'in +([^ ]+)[ |\n|$]*', line)
        if(fun == []):
            fun = 'NULL'
        else:
            fun = fun[0]
        source = re.findall(r' *([^ ]+):', line)
        if(source == []):
            source = 'NULL'
        else:
            source = source[0]
        lnumber = re.findall(r':([0-9]+)', line)
        if(lnumber == []):
            lnumber = 'NULL'
        else:
            lnumber = lnumber[0]
        res += addr + fun + source + lnumber
        stack_number += 1

    if(hash(res) in uniq_crash_hash):
        return False
    else:
        uniq_crash_hash.append(hash(res))
        return True

def run_target_with_gdb(target_path, target_args, target_crash):
    if('@@' in target_args):
        target_args = "r " + target_args.replace('@@', target_crash)
    else:
        target_args = "r " + target_args + ' < ' + target_crash
    f = open("/tmp/.script.py", "w")
    script = ('''import os
import time
import gdb
f = open(\'%s\', \'w\') #hang input detect
f.close()
gdb.execute(\'file %s')
gdb.execute(\'%s 1>/dev/null 2>/dev/null\')
os.remove(\'%s\')
gdb.execute('set logging file %s')
gdb.execute('set logging overwrite on')
gdb.execute('set logging on')
c_pid = gdb.selected_inferior().pid
if(c_pid == 0): #normal input
    time.sleep(10)
else:           #crashing input
    gdb.execute(\'bt\')
gdb.execute(\'quit\')
'''% (hang_file, target_path, target_args, hang_file, log_file))
    f.write(script)
    f.close()

    pid = os.fork()
    if(pid == 0):
        fd = os.open("/dev/null", os.O_WRONLY);
        os.dup2(fd,1)
        os.dup2(fd,2)
        sys.stdout.flush()
        os.execl('/usr/bin/gdb', 'gdb', '-x', '/tmp/.script.py')
    else:
        i=0
        while(True):
            time.sleep(0.2)
            i+=0.2
            w_pid, w_status = os.waitpid(pid, os.WNOHANG)
            if(w_pid > 0):
                if(uniq_crash_determine()):   #unique
                    print("\033[32m" + "[+] U " + target_crash  + "\033[0m")
                    os.system("cat %s" % (log_file))
                else:   #duplicate
                    print("\033[91m" + "[+] D " + target_crash  + "\033[0m")
                os.remove(log_file)
                return
            if(i>5):
                break
        if(os.path.exists(hang_file)):
            print("\033[91m" + "[+] H " + target_crash  + "\033[0m")
        else:  #normal
            print("\033[91m" + "[+] N " + target_crash  + "\033[0m")
        os.remove(log_file)

if __name__ == "__main__":
    crash_dir, target_path, target_args = input_parser()
    f_crash = open(crash_file, 'a+')

    files = os.listdir(crash_dir)
    for f in files:
        if(os.path.isfile(crash_dir+'/'+f)):
            run_target_with_gdb(target_path, target_args, crash_dir + '/' + f)

    f_crash.close()
    if(os.path.exists(hang_file)):
        os.remove(hang_file)
