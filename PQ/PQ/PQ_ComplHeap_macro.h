#ifndef PQ_COMPLHEAP_MACRO_H_
#define PQ_COMPLHEAP_MACRO_H_

//以下所写的n均表示传入的堆的size（实际堆的size可以比它大，因为可以对堆的一部分进行操作)
//i均代表操作的结点的秩（物理实现是数组）
//PQ均代表传入的数组指针
#define Parent(i) (((i) - 1) >> 1) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define LChild(i) (((i) << 1) + 1) //PQ[i]的左孩子
#define RChild(i) (((i) + 1) << 1) //PQ[i]的右孩子
#define LastInternal(n)   Parent( n - 1 ) //最后一个内部节点（即末节点的父亲）
#define ParentValid(i) ((i) > 0)  //判断PQ[i]是否有父亲
#define InHeap(n, i) ((i) >= 0 && (i) < (n)) //判断PQ[i]是否合法
#define LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有一个（左）孩子
#define RChildValid(n, i) InHeap(n, RChild(i)) //判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j) (lessthan(PQ[i], PQ[j]) ? j : i) //返回其值较大者的秩
#define ProperParent(PQ, n, i) /*其值为父子(至多)三者中的最大者的秩*/\
		(RChildValid(n, i) ? Bigger(PQ, (Bigger(PQ, i, LChild(i))), RChild(i)) \
						   : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i)) 
 //PQ[i]有两个孩子，返回三者中最大者的秩
 //PQ[i]有一个孩子，返回两者中最大者的秩
 //PQ[i]无孩子，返回i /*相等时父节点优先，如此可避免不必要的交换*/



#endif
