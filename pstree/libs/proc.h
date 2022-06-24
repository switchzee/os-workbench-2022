#include "procutils.h"
typedef struct PsNode
{
    const char *pName;
    const char *pid;
    struct PsNode *rsib, *lson;
} PsNode;

PsNode *createPsNodeFull(const char *,
                         const char *,
                         PsNode *,
                         PsNode *);
PsNode *createPsNodeWithNameId(const char *,
                               const char *);
PsNode *createPsNodeWithId(const char *);
void insertSib(PsNode *, PsNode *);
void insertSon(PsNode *, PsNode *);
PsNode *insert(PsNode *, PsNode *);
PsNode *searchByPid(PsNode *, const char *);
PsNode *searchByNode(PsNode *, PsNode *);
void printPsNode(PsNode *);
void printPsTree(PsNode *, int);

PsNode *createPsNodeFull(const char *name,
                         const char *pid,
                         PsNode *rsib,
                         PsNode *lson)
{
    PsNode *res = (PsNode *)malloc(sizeof(PsNode));
    res->pName = name;
    res->pid = pid;
    res->rsib = rsib;
    res->lson = lson;
    return res;
}

PsNode *createPsNodeWithNameId(const char *name,
                               const char *pid)
{
    return createPsNodeFull(name, pid, NULL, NULL);
}

PsNode *createPsNodeWithId(const char *pid)
{
    const char *pName = getPidName(pid);
    return createPsNodeWithNameId(pName, pid);
}

void insertSib(PsNode *head, PsNode *node)
{
    assert(head != NULL && node != NULL);
    node->rsib = head->rsib;
    head->rsib = node;
}

void insertSon(PsNode *p, PsNode *c)
{
    assert(p != NULL);
    if (p->lson != NULL)
        insertSib(p->lson, c);
    else
        p->lson = c;
}

PsNode *insert(PsNode *root, PsNode *node)
{
    PsNode *treeNode = searchByPid(root, node->pid);
    if (treeNode == NULL)
    {
        PsNode *parNode = createPsNodeWithId(getPPid(node->pid));
        treeNode = insert(root, parNode);
        insertSon(treeNode, node);
        return node;
    }
    return treeNode;
}

PsNode *searchByPid(PsNode *root, const char *pid)
{
    if (root == NULL)
        return NULL;
    if (strcmp(root->pid, pid) == 0)
        return root;
    PsNode *lres = searchByPid(root->lson, pid);
    if (lres != NULL)
        return lres;
    return searchByPid(root->rsib, pid);
}

PsNode *searchByNode(PsNode *root, PsNode *node)
{
    return searchByPid(root, node->pid);
}

void printPsNode(PsNode *root)
{
    if (root->lson == NULL)
        printf("{%s(%s)}\n", root->pName, root->pid);
    else
        printf("%s(%s)\n", root->pName, root->pid);
}

void printPsTree(PsNode *root, int spaceCnt)
{
    if (root != NULL)
    {
        printSpace(spaceCnt);
        printPsNode(root);

        PsNode *cur = root->lson;
        while (cur)
        {
            printPsTree(cur, spaceCnt + 4);
            cur = cur->rsib;
        }
    }
}

PsNode **getChilds(PsNode *root, const char *pid, int *len)
{
    PsNode *node = searchByPid(root, pid);
    assert(node != NULL);
    *len = 0;
    for (PsNode *cur = node->lson; cur; cur = cur->rsib)
        (*len)++;
    PsNode **childs = (PsNode **)malloc(sizeof(PsNode *) * (*len));
    int in = 0;
    for (PsNode *cur = node->lson; cur; cur = cur->rsib)
        childs[in++] = cur;
    return childs;
}

int PsNodeCmp(const void *a, const void *b)
{
    PsNode **na = (PsNode **)a;
    PsNode **nb = (PsNode **)b;
    return getNumber((*na)->pid) - getNumber((*nb)->pid);
}
