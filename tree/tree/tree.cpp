// tree.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <cmath>

using namespace std;
static int def = 100;
static int cnt = 2;
float make_rand()
{
	return ((float)(rand())/def);
}
float make_rand(float first, float end)
{
	
	//int rand_value = rand()%((int)(end*def - first*def)) + (int)first*def;
	
	//return ((float)rand_value/def);
	return (first+end)/2;
}
struct TreeNode {
	float value;
	TreeNode *left; // must be null, if no left child
	TreeNode *right; // must be null, if no right child
};
void sort(std::vector<float> *pNums)
{
	for (int i =0; i<pNums->size(); i++)
		for (int j = i + 1; j<pNums->size(); j++)
		{
			if ((*pNums)[j] < (*pNums)[i])
			{
				float temp = (*pNums)[i];
				(*pNums)[i] = (*pNums)[j];
				(*pNums)[j] = temp;
			}			
		}
}

// generate_tree() must return a pointer to root node

TreeNode *generate_tree( std::vector<float> nums) {
	if (nums.size()==0)
		return NULL;
	cnt = nums.size();
	sort(&nums);
	for (int i = 0; i< cnt; i++)
	{
		cout << nums [i];
		cout<< " ";
	}
	cout<<endl;
	TreeNode *pNode = NULL;
	
	int size_mass = nums.size();
	int levels_count = 0;
	while ((double)nums.size() > (int)pow(2, levels_count))
	{
		levels_count++;
	}
	vector<float> buff_nums;
	for (int i = 0; i < (int)pow(2, levels_count) - nums.size(); i++)
	{
		buff_nums.push_back(make_rand()/def + nums[nums.size()-1]);
	}
	
	sort(&buff_nums);
	int level_indx = 0;
	
	std::vector<TreeNode*> up_nodes;
	std::vector<TreeNode*> current_nodes;
	while(level_indx<= levels_count)
	{
		int node_indx_on_line=0;
		int delta = nums.size() - (int)pow(2, levels_count - 1);
		double val = (double)delta / pow(2, levels_count - level_indx);
		if (val - (int)val > 0.00001)
			val += 1;

		while (node_indx_on_line < (int)(pow(2, (double)level_indx)) / 2 + (int)val)
		{
			TreeNode *MyTreeNode=new TreeNode; 
			if (level_indx == 0)
				pNode = MyTreeNode;
			if (level_indx != levels_count)
			{
				int first_indx =node_indx_on_line*(int)pow(2, (double)levels_count - level_indx);
				int end_ind =(node_indx_on_line+1)*(int)pow(2, (double)levels_count - level_indx) - 1;
				
				if (up_nodes.size())
				{
					if (end_ind >= nums.size())
					{
						int inx_first_calc = (first_indx + end_ind) / 2;
						if (inx_first_calc >= nums.size())
						{
							inx_first_calc -= nums.size();
							MyTreeNode->value = make_rand(buff_nums[inx_first_calc], buff_nums[inx_first_calc + 1]);
						}
						else
							MyTreeNode->value = make_rand(nums[inx_first_calc], buff_nums[0]);

					}
					else
						MyTreeNode->value = make_rand(nums[(first_indx + end_ind) / 2], nums[(first_indx + end_ind) / 2 + 1]);
				}
				else
				{
					MyTreeNode->value = make_rand(nums[end_ind / 2 ], nums[end_ind / 2 + 1]);
				}			
			}
			else
			if (node_indx_on_line<nums.size())
				MyTreeNode->value=nums[node_indx_on_line];
			if (node_indx_on_line < nums.size())
			{
				MyTreeNode->left = MyTreeNode->right = NULL;
				current_nodes.push_back(MyTreeNode);
			}
			node_indx_on_line++;
		}
		for (int i = 0; i < up_nodes.size(); i++)
		{
			if (i*2< current_nodes.size())
				up_nodes[i]->left = current_nodes[i*2];
			if (i*2+1< current_nodes.size())
				up_nodes[i]->right = current_nodes[i*2 + 1];	
		}
		up_nodes.clear();
		for (int i = 0; i < current_nodes.size(); i++)
		{
			up_nodes.push_back(current_nodes[i]);
		}
		current_nodes.clear();
			
		level_indx++;
	}
	return pNode;	
}
void print_Tree(TreeNode * p,int level)
{
	if(p)
	{
		print_Tree(p->left,level + 1);
		for(int i = 0;i< level;i++) 
			cout<<"   ";
		cout << p->value << endl;
		print_Tree(p->right,level + 1);
	}
}
void show(TreeNode *&Tree) 
{
	print_Tree(Tree,0);
}



int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<float> nums;
	/*for (int i = 0; i< cnt; i++)
	{
		nums.push_back(make_rand()); 
		cout << nums [i];
		cout<< " ";
	}*/
	nums.push_back(0.11);
	nums.push_back(0.44);
	nums.push_back(0.85);
	nums.push_back(0.56);
	nums.push_back(0.59);
	nums.push_back(0.65);
	//cout<< endl;
	TreeNode* tree = generate_tree(nums);
	if (tree!=NULL)
		show(tree);

	int val;
	cin>>val;
	return 0;
}
