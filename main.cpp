//
//  main.cpp
//  Triple Merge
//
//  Created by Michael Mathews on 9/1/22.
//  Copyright © 2022 L&L. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
 
void merge(vector<int> &array, vector<int> &result, int front, int mid1, int mid2, int back){
    int index1 = front, index2 = mid1, index3 = mid2, indexResult = front;
 
    //iterate through, merging 3 arrays
    while ((index1 < mid1) && (index2 < mid2) && (index3 < back)){
        if(array[index1] < array[index2]){
            if(array[index1] < array[index3]){
                result[indexResult] = array[index1];
                index1++;
            }
            else {
                result[indexResult++] = array[index3];
                index3++;
            }
            indexResult++;
        }
        else {
            if(array[index2] < array[index3]){
                result[indexResult] = array[index2];
                index2++;
            }
            else {
                result[indexResult] = array[index3];
                index3++;
            }
            indexResult++;
        }
    }
 
    //1st and 2nd have values left
    while ((index1 < mid1) && (index2 < mid2)){
        if(array[index1] < array[index2]){
            result[indexResult] = array[index1];
            index1++;
        }
        else{
            result[indexResult] = array[index2];
            index2++;
        }
        indexResult++;
    }
 
    //2nd and 3rd have values left
    while ((index2 < mid2) && (index3 < back)){
        if(array[index2] < array[index3]){
            result[indexResult] = array[index2];
            index2++;
        }
        else{
            result[indexResult] = array[index3];
            index3++;
        }
        indexResult++;
    }
 
    //1st and 3rd have values left
    while ((index1 < mid1) && (index3 < back)){
        if(array[index1] < array[index3]){
            result[indexResult] = array[index1];
            index1++;
        }
        else{
            result[indexResult] = array[index3];
            index3++;
        }
        indexResult++;
    }
 
    //copy values from 1st
    while (index1 < mid1){
        result[indexResult] = array[index1];
        index1++;
        indexResult++;
    }
    //copy values from 2nd
    while (index2 < mid2){
        result[indexResult] = array[index2];
        index2++;
        indexResult++;
    }
    //copy values from 3rd
    while (index3 < back){
        result[indexResult] = array[index3];
        index3++;
        indexResult++;
    }
}
 

void mergeSortSplit(vector<int> &array, vector<int> &result, int front, int back){
    //make sure array size not 1 or smaller
    if (back - front > 1){
        //find indexes to split array 3 times
        int mid1 = front + ((back - front) / 3);
        int mid2 = front + ((back - front) / 3) *2 + 1;
     
        //recursive split
        mergeSortSplit(result, array, front, mid1);
        mergeSortSplit(result, array, mid1, mid2);
        mergeSortSplit(result, array, mid2, back);
     
        //merge arrays
        merge(result, array, front, mid1, mid2, back);
    }
}
 
void mergeSort3(vector<int> &array, int size){
    const int front = 0;
    //check to make sure array has elements
    if (size != front){
        vector<int> copy(size);
        //copy elements
        for (int i = 0; i < size; i++){
            copy[i] = array[i];
        }
        //call to recursive splitting funciton
        mergeSortSplit(copy, array, front, size);

        for (int i = 0; i < size; i++){
            array[i] = copy[i];
        }
    }
}

int main(){
    vector<int> nums;
    ifstream inputFile;
    ofstream outputFile;
    string fileName;
    int count = 0, num;
    
    cout << "Enter a file name: ";
    cin >> fileName;
    
    //make sure file oopen
    inputFile.open(fileName);
    if(!inputFile){
        cout << "Error: File not open" << endl;
        return 1;
    }
    
    //get numbers
    while(inputFile >> num){
        nums.push_back(num);
        count++;
    }
    inputFile.close();
    
    mergeSort3(nums, count);
    
    //write to output file
    outputFile.open("sorted.txt");
    for(int i = 0; i < count; i++){
        outputFile << nums[i] << endl;
    }
    outputFile.close();
    
    return 0;
}
