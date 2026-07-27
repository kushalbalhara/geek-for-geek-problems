class Solution {
public:
    int preIndex = 0;

    Node* solve(vector<int>& pre, vector<int>& preMirror,
                int l, int h,
                unordered_map<int,int>& mp) {

        if (preIndex >= pre.size() || l > h)
            return NULL;

        Node* root = new Node(pre[preIndex++]);

        if (l == h || preIndex >= pre.size())
            return root;

        int idx = mp[pre[preIndex]];

        root->left = solve(pre, preMirror, idx, h, mp);
        root->right = solve(pre, preMirror, l + 1, idx - 1, mp);

        return root;
    }

    Node* constructBinaryTree(vector<int>& pre, vector<int>& preMirror) {

        unordered_map<int,int> mp;

        for (int i = 0; i < preMirror.size(); i++)
            mp[preMirror[i]] = i;

        preIndex = 0;

        return solve(pre, preMirror, 0, preMirror.size() - 1, mp);
    }
};