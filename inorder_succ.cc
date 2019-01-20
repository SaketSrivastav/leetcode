#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int n): val(n), left(NULL), right(NULL) {}
};

class BSTree {
private:
    TreeNode *root;
    stack<TreeNode *> nodeStack;
public:
    BSTree() {
        root = NULL;
    }

    BSTree(TreeNode * root1) {
        root = root1;
    }

    BSTree(int x) {
        root = new TreeNode(x);
    }

    void begin() {
        TreeNode * node, *nodeL;

        if(root == NULL) return;

        node = root;

        nodeStack.push(node);

        // Push all lefts of root node on to stack
        if(node->left != NULL) {
            nodeL = node->left;
            cout << "Push: " ;
            while(nodeL != NULL){
                nodeStack.push(nodeL);
                cout << nodeL->val << " ";
                nodeL = nodeL->left;
            }
            cout << endl;
        }
    }

    bool hasNext()
    {
        // Nodestack represents the stack of smallest elements of the given BST
        return nodeStack.size();
    }

    int next()
    {
        TreeNode *node, *nodeL;
        node = nodeStack.top();
        nodeStack.pop();
        cout << "Pop: " << node->val << endl;

        // Push lefts of the right node, because they will be next smallest elements
        if(node->right != NULL) {
            nodeStack.push(node->right);
            cout << "Push: " << node->right->val << " ";
            nodeL = node->right->left;
            while(nodeL) {
                nodeStack.push(nodeL);
                cout << nodeL->val << " ";
                nodeL = nodeL->left;
            }
            cout << endl;
        }

        return node->val;
    }

    void insert(int x) {
        TreeNode *copy = root;
        if(copy == NULL) {
            root = new TreeNode(x);
            return;
        }

        while(copy != NULL) {
            if(x <= copy->val)
            {
                if(copy->left == NULL) {
                    copy->left = new TreeNode(x);
                    break;
                }
                else
                    copy = copy->left;
            }
            else {
                if(copy->right == NULL) {
                    copy->right = new TreeNode(x);
                    break;
                }
                else
                    copy = copy->right;
            }
        }

        return;
    }

    TreeNode * search(int x) {
        TreeNode * copy = root;
        while(copy != NULL) {
            if(x < copy->val)
                copy = copy->left;
            else if(x > copy->val)
                copy = copy->right;
            else {
                return copy;
            }
        }

        return NULL;
    }

    void deleteNode(int x) {
        TreeNode * nodeD;

        cout << "Deleting node " << x << endl;
        if(root == NULL) return;

        nodeD = root;
        while(nodeD != NULL) {
            if(x < nodeD->val)
                nodeD = nodeD->left;
            else if (x > nodeD->val)
                nodeD = nodeD->right;
            else
                break;
        }

        //Case 1: no children
        if(!nodeD->left && !nodeD->right)
        {
            cout << "case 1: " << nodeD->val << " has no children" << endl;
            delete nodeD;
        }

        //case 2: one child, left/right
        if(nodeD->left && !nodeD->right) {
            nodeD->val = nodeD->left->val;
            delete nodeD->left;
            nodeD->left = NULL;
            cout << "Deleted left child of " << x << endl;
            return;
        }

        if(nodeD->right && !nodeD->left) {
            nodeD->val = nodeD->right->val;
            delete nodeD->right;
            nodeD->right = NULL;
            cout << "Deleted right child of " << x << endl;
            return;
        }

        // case 3: both children, swap with min on right subtree
        //         which is nothing but the inorder successor
        if(nodeD->left && nodeD->right) {
            TreeNode * succ = inorderSucc(nodeD->right->val);
            int tmp;
            if(succ)
            {
                cout << "Swapping inorderSucc " << succ->val << " and "
                     << nodeD->val << endl;
                tmp = nodeD->val;
                nodeD->val = succ->val;
                succ->val = tmp;
                delete succ;
            }

            return;
        }
    }

    void inorderHelper(TreeNode * node) {
        if(node == NULL) return;

        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }

    void inorder() {
        TreeNode * copy = root;
        inorderHelper(copy);
        cout << endl;
    }

    TreeNode * minValue(TreeNode *node)
    {
        while(node->left != NULL) {
            node = node->left;
        }

        return node;
    }

    TreeNode * inorderSucc(int x) {
        TreeNode * tmp = NULL, *succ = NULL;
        tmp = search(x);
        if(tmp == NULL) return NULL;

        // Inorder successor for a node whose right child is not empty
        // is the min element in its right subtree
        if(tmp->right != NULL)
            return minValue(tmp->right);

        // Inorder successor for a node whose right child is empty
        // is the nearest ancestor where x is in its left subtree.
        tmp = root;
        while(tmp != NULL) {
            if(x < tmp->val) {
                succ = tmp;
                tmp = tmp->left;
            } else if(x > tmp->val) {
                tmp = tmp->right;
            } else {
                break;
            }
        }
        return succ;
    }

};

int main(int argc, char *argv[])
{
    BSTree bst = BSTree();
    TreeNode * result = NULL;

    bst.insert(20);
    bst.insert(8);
    bst.insert(4);
    bst.insert(22);
    bst.insert(12);
    bst.insert(10);
    bst.insert(14);

    bst.inorder();

    result = bst.inorderSucc(14);
    if(result != NULL)
        cout << "Inorder successor of 14 : " << result->val << endl;
    else
        cout << "Inorder successor of 14 : not found" << endl;

    bst.deleteNode(10);
    bst.deleteNode(8);
    bst.deleteNode(20);

    bst.inorder();
    // cout << "Test BSTIterator: " << endl;
    // bst.begin();
    // while (bst.hasNext())
    // {
    //     cout << bst.next() << " ";
    // }
    // cout << endl;

    return 0;
}
