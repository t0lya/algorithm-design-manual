#include <stdio.h>
#include <stdlib.h>

typedef struct Bin
{
    float weight;
    struct Bin *parent;
    struct Bin *left;
    struct Bin *right;
} Bin;

Bin *leftmostChild(Bin *bin)
{
    if (bin == NULL || bin->left == NULL)
    {
        return bin;
    }

    return leftmostChild(bin->left);
}

void freeBin(Bin *bin)
{
    if (bin == NULL)
    {
        return;
    }

    freeBin(bin->left);
    freeBin(bin->right);
    free(bin);
}

void printBin(Bin *bin)
{
    if (bin == NULL)
    {
        return;
    }

    printBin(bin->left);
    printf("%f\n", bin->weight);
    printBin(bin->right);
}

Bin *getBin(Bin *bin, float weight)
{
    if (bin == NULL || bin->weight == weight)
    {
        return bin;
    }

    if (bin->weight > weight)
    {
        return getBin(bin->left, weight);
    }
    else
    {
        return getBin(bin->right, weight);
    }
}

int deleteBin(Bin **root, float weight)
{
    Bin *bin = getBin(*root, weight);

    if (bin == NULL)
    {
        return 0;
    }

    if (bin->left == NULL && bin->right == NULL)
    {
        if (*root == bin)
        {
            *root = NULL;
        }
        else if (bin->parent->left->weight == bin->weight)
        {
            bin->parent->left = NULL;
        }
        else if (bin->parent->right->weight == bin->weight)
        {
            bin->parent->right = NULL;
        }

        free(bin);
        return 1;
    }

    if (bin->left == NULL || bin->right == NULL)
    {
        Bin *child = (bin->left == NULL) ? bin->right : bin->left;
        bin->weight = child->weight;
        bin->right = child->right;
        bin->left = child->left;
        free(child);
        return 1;
    }

    Bin *leftmostRight = leftmostChild(bin->right);
    bin->weight = leftmostRight->weight;
    leftmostRight->parent->left = NULL;
    free(leftmostRight);
    return 1;
}

void insertBin(float binWeight, Bin **bin, Bin *parent)
{
    if (bin == NULL)
    {
        return;
    }

    if (*bin == NULL)
    {
        Bin *tmp = malloc(sizeof(Bin));
        tmp->weight = binWeight;
        tmp->parent = parent;
        tmp->left = tmp->right = NULL;
        *bin = tmp;
        return;
    }

    if (binWeight < (*bin)->weight)
    {
        insertBin(binWeight, &((*bin)->left), *bin);
    }
    else
    {
        insertBin(binWeight, &((*bin)->right), *bin);
    }

    return;
}

int insertWeight(float weight, Bin **bin, Bin **root)
{
    if (bin == NULL)
    {
        return 0;
    }

    if (*bin == NULL)
    {
        insertBin(weight, root, NULL);
        return 1;
    }

    float newWeight = weight + (*bin)->weight;
    if (newWeight > 1)
    {
        return insertWeight(weight, &((*bin)->left), root);
    }
    else
    {
        float test = (*bin)->weight;
        deleteBin(root, (*bin)->weight);
        insertBin(newWeight, root, NULL);

        return 0;
    }
}

int binAmount(float weights[], size_t length)
{
    if (length == 0)
    {
        return 0;
    }

    Bin *root = malloc(sizeof(Bin));
    root->weight = 0.0f;
    root->parent = root->left = root->right = NULL;
    int binCount = 1;
    for (size_t i = 0; i < length; i++)
    {
        binCount += insertWeight(weights[i], &root, &root);
    }

    printBin(root);
    freeBin(root);
    return binCount;
}

int main()
{
    float test1[] = {0, 0, 0, 0, 0, 0, 0, 0};
    float test2[] = {1, 1, 1, 1, 1, 1};
    float test3[] = {.4, .8, .1, .4, .7};

    printf("Bin count: %d\n", binAmount(test3, sizeof test3 / sizeof *test3));
    printf("Bin count: %d\n", binAmount(test1, sizeof test1 / sizeof *test1));
    printf("Bin count: %d\n", binAmount(test2, sizeof test2 / sizeof *test2));
}
