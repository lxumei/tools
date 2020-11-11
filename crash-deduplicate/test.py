import re

log_file = 'crash-log'
def uniq_crash_determine():
    lines = open(log_file, 'r').readlines()

    new_lines =[]
    for i in range(0, len(lines)):
        if(lines[i][0] == '#'):
            new_lines.append(lines[i])
        else:
            new_lines[-1] = new_lines[-1].strip('\n') + lines[i]
    res = []
    addr = fun = source = lnumber = ''
    for line in new_lines:

        addr = re.findall(r"#\d+ +(.+) in", line)
        if(addr == []):
            addr = 'NULL'
            fun = re.findall(r"(.+) +\("  ,re.findall(r" +(.+) +at", line)[0])[0]
        else:
            addr = addr[0]
            fun = re.findall(r"(.+) +\("  ,re.findall(r"in +(.+) +at", line)[0])[0]
        source = re.findall(r"at +(.+):", line)[0]
        lnumber = re.findall(r":(.+)", line)[0]
        print(line.strip('\n'))
        print(addr, fun, source, lnumber)
        print('\n')

    return

def crash_determine():
    lines = open(log_file, 'r').readlines()

    new_lines =[]
    for i in range(0, len(lines)):
        if(lines[i][0] == '#'):
            new_lines.append(lines[i])
        else:
            new_lines[-1] = new_lines[-1].strip('\n') + lines[i]

    res = []
    addr = fun = source = lnumber = ''
    for line in new_lines:
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
        print(line.strip('\n'))
        print(addr, fun, source, lnumber)
        print('\n')
        res.append([addr, fun, source, lnumber])
        print(res)

    return

if __name__ == '__main__':
    crash_determine()
