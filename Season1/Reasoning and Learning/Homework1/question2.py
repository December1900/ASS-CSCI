# Student Name:Xiao Yao, Student Number:2019180015|6641751
from math import log
import operator


def cal_entropy(dataSet):
    totalNum = len(dataSet)
    labels ={}
    for data in dataSet:
        lable=data[-1]
        if lable not in labels.keys():
            labels[lable]=0
        labels[lable]+=1
    ShanEntropy=0.0
    for key in labels:
        prob = float(labels[key]) / totalNum
        ShanEntropy -= prob * log(prob, 2)
    return ShanEntropy

def split_data(dataSet,axis,value):
    ret_data=[]
    for featVec in dataSet:
        if featVec[axis]==value : 
            reduceFeatVec=featVec[:axis]
            reduceFeatVec.extend(featVec[axis+1:])
            ret_data.append(reduceFeatVec)
    return ret_data 

def chooseMaxFeatureID3(dataSet):
    numFeature=len(dataSet[0])-1
    baseEntropy=cal_entropy(dataSet)
    biggestInforGain=0
    bestFeature=-1
    for i in range(numFeature):
        featList=[number[i] for number in dataSet]
        uniqualVals=set(featList) 
        newEntropy=0
        for value in uniqualVals:
            subDataSet=split_data(dataSet,i,value)
            prob=len(subDataSet)/float(len(dataSet)) 
            newEntropy+=prob*cal_entropy(subDataSet)
        infoGain=baseEntropy-newEntropy
        if (infoGain>biggestInforGain):
            biggestInforGain=infoGain
            bestFeature=i
    return bestFeature 

def most_cnt(classList):
    CntCount={}
    for vote in classList:
        if vote not in CntCount.keys():CntCount[vote]=0
        CntCount[vote]+=1
    sortedClassCount=sorted(CntCount.items,key=operator.itemgetter(1),reversed=True)
    return sortedClassCount[0][0]

def createID3Tree(dataSet,labels):
    classList=[example[-1] for example in dataSet]
    if classList.count(classList[0])==len(classList):
        return classList[0]
    if len(classList[0])==1:
        return most_cnt(classList)
    bestFeature=chooseMaxFeatureID3(dataSet)
    currentFeatLable=labels[bestFeature] 
    myTree={currentFeatLable:{}} 
    del(labels[bestFeature]) 
    featValues=[example[bestFeature] for example in dataSet]
    uniqueVals=set(featValues)
    for value in uniqueVals:
        subLables=labels[:] 
        myTree[currentFeatLable][value]=createID3Tree(split_data(dataSet,bestFeature,value),subLables)
    return myTree
    

def convert(node,results):
    if(type(node)==dict):
        for key in node:
            if(type(node[key])==dict):
                current = ""
                for subKey in node[key].keys():
                    current += "(" + key + " " + subKey + " "
                    if(isinstance (node[key][subKey],str)):
                        current += convert(node[key][subKey],"(")
                    else:
                        current += convert(node[key][subKey],"")
                    current += ")"
            results += current
        return results
    else:
        results += node + ")"
        return results

fr=open('data.txt')
lenses = [value.strip().split() for value in fr.readlines()]
lensesLabels = lenses[0]
del lenses[0]



trees = createID3Tree(lenses,lensesLabels)

result = ""


print(trees)
print("(" + convert(trees,result) + ")")
