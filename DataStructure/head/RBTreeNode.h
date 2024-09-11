template <class K, class V>
struct RBTreeNode
{
    RBTreeNode<K, V> *_left;
    RBTreeNode<K, V> *_right;
    RBTreeNode<K, V> *_parent;

    pair<K, V> _kv;
    Colour _col;

    RBTreeNode(const pair<K, V> &kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _col(RED) // 将新插入的节点 初始化为 红色！
    {
    }

    template <class K, class V>
    class RBTree
    {
        typedef RBTreeNode<K, V> Node;

        // 构造函数
        RBTree()
            : _root(nullptr)
        {
        }

        bool Insert(const pair<K, V> &kv)
        {
            if (_root == nullptr)
            {
                _root = new Node(kv);
                // 注意：因为是红黑树，所以必须保证根节点是黑色的
                _root->_col = BLACK;
                return true;
            }

            Node *cur = _root;
            Node *parent = nullptr;
            while (cur)
            {
                if (kv.first < cur->_kv.first)
                {
                    parent = cur;
                    cur = cur->_left;
                }
                else if (kv.first > cur->_kv.first)
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else
                {
                    return false; // 不允许重复 相同的直接false
                }
            }
            cur = new Node(kv);
            cur->_col = RED; // 默认：新插入的结点 为红色节点！

            if (kv.first < parent->_kv.first)
            {
                parent->_left = cur;
            }
            else
            {
                parent->_right = cur;
            }
            cur->_parent = parent;

            // 此时已经算是插入上了，如果cur的parent是黑色就此结束，但是红色就需要调整了！
        }

        bool Insert(const pair<K, V> &kv)
        {
            if (_root == nullptr)
            {
                _root = new Node(kv);
                // 注意：因为是红黑树，所以必须保证根节点是黑色的
                _root->_col = BLACK;
                return true;
            }

            Node *cur = _root;
            Node *parent = nullptr;
            while (cur)
            {
                if (kv.first < cur->_kv.first)
                {
                    parent = cur;
                    cur = cur->_left;
                }
                else if (kv.first > cur->_kv.first)
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else
                {
                    return false;
                }
            }
            cur = new Node(kv);
            cur->_col = RED; // 默认：新插入的结点 为红色节点！

            if (kv.first < parent->_kv.first)
            {
                parent->_left = cur;
            }
            else
            {
                parent->_right = cur;
            }
            cur->_parent = parent;

            // 此时已经算是插入上了，如果cur的parent是黑色就此结束，但是红色就需要调整了！

            while (parent && parent->_col == RED)
            // 这里的 parent && parent->_col == RED 中的 第1个parent就是来判断g是不是root
            {
                Node *grandfather = parent->_parent;

                // 1、变量uncle在grandfather的右边
                if (parent == grandfather->_left)
                {
                    //(1)uncle存在&&为红   -------------// 变色
                    Node *uncle = grandfather->_right;

                    if (uncle && uncle->_col == RED)
                    {
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;

                        // 还要判断 此时的grandfather是不是root
                        //  ①g == root只需要让 g再次变黑即可！
                        //  ②g != root  把g赋值给cur 继续往上更新！
                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    // (2)uncle不存在 || uncle存在 && 为黑色    ----// 变色 + 旋转
                    else
                    {
                        /*parent->_col = BLACK;
                        grandfather->_col = RED;*/

                        // 旋转：单旋 、双旋
                        if (cur == parent->_left)
                        {
                            // (1)单旋
                            //     g
                            //   p   u
                            // c

                            先变色 再旋转！

                                // parent->_col = BLACK;
                                // grandfather->_col = RED;
                                // RS_rotation(grandfather);

                                // 先旋转 再变色！
                                RS_rotation(grandfather);
                            parent->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        else
                        {
                            // (1)双旋
                            //       g
                            //   p      u
                            //     c

                            先变色 再旋转！
                                // cur->_col = BLACK;
                                // grandfather->_col = RED;
                                // LS_rotation(parent);
                                // RS_rotation(grandfather);

                                // 先旋转 再变色！
                                LS_rotation(parent);
                            RS_rotation(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }

                        break; // 因为else这种情况 变色：没有破坏规则  旋转：维持了红黑树的性质 所以完成之后可以直接 退出循环！
                    }
                }
                else
                // 2、变量uncle在grandfather的左边
                {
                    Node *uncle = grandfather->_left;

                    // (1)
                    if (uncle && uncle->_col == RED)
                    {
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;

                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    else // (2)
                    {

                        if (cur == parent->_right)
                        {

                            ①
                                //parent->_col = BLACK;
                                // grandfather->_col = RED;
                                // LS_rotation(grandfather);

                                // 先旋转 再变色！
                                LS_rotation(grandfather);
                            parent->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        else
                        {

                            ②
                                //parent->_col = BLACK;
                                // grandfather->_col = RED;
                                // RS_rotation(parent);
                                // LS_rotation(grandfather);

                                // 先旋转 再变色！
                                RS_rotation(parent);
                            LS_rotation(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        break; // 因为else这种情况 变色：没有破坏规则  旋转：维持了红黑树的性质 所以完成之后可以直接 退出循环！
                    }
                }
            }
            _root->_col = BLACK;
            return true;
        }

        // 查找
        Node *Find(const K &key)
        {
            Node *cur = _root;
            while (cur)
            {
                if (cur->_kv.first < key) // key比当前节点小，就向右查找
                {
                    cur = cur->_right;
                }
                else if (cur->_kv.first > key) // key比当前节点大，就向左查找
                {
                    cur = cur->_left;
                }
                else // 找到了
                {
                    return cur;
                }
            }
            return nullptr; // 空树，直接返回
        }

        bool Is_balance() // 主要就是 判断 这个树 符不符合 那4个规则！
        {
            if (_root->_col == RED)
            {
                return false; // 不符合 规则2 ：根节点必须是黑色！
            }

            // 创建 一个 refNum 当做参照物 用来检验是否和blackNum相等 从而得出结论：blackNum思路正确 && 整个树符合规则4、
            // refNum 可以是 最左侧/最右侧！

            // int refNum = 1;  因为根节点是黑色 为啥初始化的时候 不直接给1？而是前置++
            int refNum = 0;
            Node *cur = _root;
            while (cur)
            {
                if (cur->_col == BLACK)
                {
                    // refNum++;   因为根节点是黑色 所以要用前置++
                    ++refNum;
                }
                cur = cur->_left;
            }

            return _Check(_root, 0, refNum);
        }

        // 遍历
        void _InOrder(Node *root)
        {
            if (root == nullptr)
            {
                return;
            }

            _InOrder(root->_left);
            cout << root->_kv.first << ":" << root->_kv.second << endl;
            _InOrder(root->_right);
        }

        void InOrder()
        {
            _InOrder(_root);
            cout << endl;
        }

        void TestRBTree1()
        {
            int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 8, 3, 1, 10, 6, 4, 7, 14, 13};

            RBTree<int, int> t1;
            for (auto e : a)
            {
                if (e == 10)
                {
                    int i = 0;
                }
                t1.Insert({e, e});

                cout << "Insert:" << e << "->" << t1.Is_balance() << endl;
            }

            t1.InOrder();

            cout << t1.Is_balance() << endl;
        }

    private:
        Node *_root;

        // 创建一个 blackNum 用来标记 每条路径下 黑色节点的数目！（递归形参！）
        bool _Check(Node *root, int blackNum, const int refNum)
        {
            if (root == nullptr)
            {
                if (refNum != blackNum)
                {
                    cout << "存在黑色结点不相等的 路径" << endl;
                    return false;
                }

                return true;
            }

            if (root->_col == RED && root->_parent->_col == RED)
            {
                cout << root->_kv.first << "存在连续的红色结点！" << endl;
                return false; // 不符合规则3： 不能存在连续的红色节点！
            }

            if (root->_col == BLACK)
            {
                blackNum++;
            }

            // 递归遍历整个树！
            return _Check(root->_left, blackNum, refNum) &&
                   _Check(root->_right, blackNum, refNum);
        }
    };
};
