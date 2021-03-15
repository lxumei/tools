class Solution {
    public:
        vector<string> res;

        void help(int n, string left, string mid, string right){
            string s;
            if(n == 1){
                s = "move from " + left + " to " + right;
                res.push_back(s);
                return;
            }

            help(n-1, left, right, mid);//left --> mid
            help(1, left, mid, right); //left --> right
            help(n-1, mid, left, right); //mid --> right
        }

        vector<string> getSolution(int n) {
            // write code here
            help(n, "left", "mid", "right");
            return res;
        }
};
