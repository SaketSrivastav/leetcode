/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result = {};
        int nodeCount = 0;
        TreeNode *node = root;

        if(root == NULL) return {};

        // BFS traversal of binary tree
        q.push(node);
        vector<int> level = {};
        while(!q.empty()) {
            int nodeCount = q.size();
            level.clear();
            while(nodeCount > 0) {
                TreeNode *curr = q.front();
                q.pop();

                level.push_back(curr->val);

                if(curr->left != NULL)
                    q.push(curr->left);
                if(curr->right != NULL)
                    q.push(curr->right);
                nodeCount--;
            }
            result.push_back(level);
        }

        return result;
    }
};
