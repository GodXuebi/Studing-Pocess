#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <random>

using namespace std;


void show(vector<int>&nums)
{
    for(int i=0;i<nums.size();i++)
    {
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}

void swap(int&a,int&b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void bubblesort(vector<int>&nums)
{
    int size = nums.size();
    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(nums[j]>nums[j+1])
            {
                int tmp = nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=tmp;
            }
        }
    }
}

void selectsort(vector<int>&nums)
{
    int size = nums.size();
    for(int i=0;i<size-1;i++)
    {
        int minindex=i;
        for(int j=i;j<size;j++)
        {
            if(nums[j]<nums[minindex])
            {
                minindex=j;
            }
        }
        if(minindex!=i)
        {
            int tmp=nums[minindex];
            nums[minindex]=nums[i];
            nums[i]=tmp;
        }
    }
}

void insertsort(vector<int>&nums)
{
    int size = nums.size();
    for(int i=1;i<size;i++)
    {
        int val = nums[i];
        int j;
        for(j=i-1;j>=0&&nums[j]>val;j--)
        {
            nums[j+1] = nums[j];
        }
        nums[j+1] = val;
    }
}

void shellsort(vector<int>&nums)
{
    int size = nums.size();
    for(int gap=size/2;gap>0;gap=gap/2)
    {
        for(int i=gap;i<size;i++)
        {
            int val=nums[i];
            int j;
            for(j=i-gap;j>=0&&nums[j]>val;j-=gap)
            {
                nums[j+gap] = nums[j];
            }
            nums[j+gap] = val;
        }
    }
}

void quicksort(vector<int>&nums,int left,int right)
{
    if(left >= right) return;
    srand(unsigned(time(NULL)));
    int size = right-left+1;
    int r = left + (random()%size);

    swap(nums[r],nums[right]);

    int index = left;
    int i = left;

    while(i<right)
    {
        if(nums[i]<nums[right])
        {
            swap(nums[i],nums[index]);
            index++;
        }
        i++;
    }
    swap(nums[right],nums[index]);
    quicksort(nums,left,index-1);
    quicksort(nums,index+1,right);

}

void merge(vector<int>&nums,int left,int mid,int right)
{
    int size1=mid-left+1;
    int size2=right-mid;
    vector<int> tmp(size1+size2);
    int i=left,j=mid+1,k=0;
    while(i<=mid&&j<=right)
    {
        if(nums[i]<nums[j])
        {
            tmp[k++]=nums[i++];
        }
        else
        {
            tmp[k++]=nums[j++];
        }
    }
    
    while(i<=mid)
    {
        tmp[k++]=nums[i++];
    }
    while(j<=right)
    {
        tmp[k++]=nums[j++];
    }
    for(int d=0;d<tmp.size();d++)
    {
        nums[left++]=tmp[d];
    }
    tmp.clear();
}

void mergesort(vector<int>&nums,int left,int right)
{
    if(left==right) return;
    int mid=(left+right)/2;
    mergesort(nums,left,mid);
    mergesort(nums,mid+1,right);
    merge(nums,left,mid,right);
}

void heap(vector<int>&nums,int i,int len)
{
    int left = 2*i,right = 2*i+1;
    int large = i;
    if(left<len&&nums[left]>nums[large])
    {
        large = left;
    }
    if(right<len&&nums[right]>nums[large])
    {
        large = right;
    }
    if(large != i)
    {
        swap(nums[large],nums[i]);
        heap(nums,large,len);
    }
    
}

void buildheap(vector<int>&nums,int len)
{
    for(int i=len/2;i>=0;i--)
    {
        heap(nums,i,len);
    }
}

void heapsort(vector<int>&nums)
{
    int len = nums.size();
    buildheap(nums,len);
    for(int i=len-1;i>0;i--)
    {
        swap(nums[0],nums[i]);
        heap(nums,0,i);
    }
}
int main(int agrc,char*argv[])
{
    vector<int> nums{2,4,1,4,8,4,3,7,9,6,0};
//------------------------------bubblesort
    vector<int> tmp(nums);
    cout<<"Before bubblesort:";
    show(tmp);
    bubblesort(tmp);
    cout<<"After bubblesort:";
    show(tmp);
    tmp.clear();
    tmp=nums;

//------------------------------selectsort
    cout<<"Before selectsort:";
    show(tmp);
    selectsort(tmp);
    cout<<"After selectsort:";
    show(tmp);
    tmp.clear();
    tmp=nums;


//------------------------------insertsort
    cout<<"Before insertsort:";
    show(tmp);
    insertsort(tmp);
    cout<<"After insertsort:";
    show(tmp);
    tmp.clear();
    tmp=nums;

//------------------------------shellsort
    cout<<"Before shellsort:";
    show(tmp);
    shellsort(tmp);
    cout<<"After shellsort:";
    show(tmp);
    tmp.clear();
    tmp=nums;

//------------------------------quicksort
    cout<<"Before quicksort:";
    show(tmp);
    quicksort(tmp,0,tmp.size()-1);
    cout<<"After quicksort:";
    show(tmp);
    tmp.clear();
    tmp=nums;

//------------------------------mergesort
    cout<<"Before mergesort:";
    show(tmp);
    mergesort(tmp,0,tmp.size()-1);
    cout<<"After mergesort:";
    show(tmp);
    tmp.clear();
    tmp=nums;
 
//------------------------------heapsort
    cout<<"Before heapsort:";
    show(tmp);
    heapsort(tmp);
    cout<<"After heapsort:";
    show(tmp);
    tmp.clear();
    tmp=nums;
    cin.get();
}