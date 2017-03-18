import numpy as np
import itertools
import operator
import os

def grouper(n, iterable, fillvalue=None):
    args = [iter(iterable)] * n
    return itertools.zip_longest(*args, fillvalue=fillvalue)
doctopic_triples = []
mallet_docnames = []
with open("/Users/omkarpatil/Documents/workspace/fake_news/fake_compostion.txt") as f:
    f.readline()  
    for line in f:
        docnum, docname, *values = line.rstrip().split('\t')
        mallet_docnames.append(docname)
        c=0
        for share in grouper(1, values):
            triple = (docname, c, (share))
            doctopic_triples.append(triple)
            c=c+1
doctopic_triples = sorted(doctopic_triples, key=operator.itemgetter(0,1))
#print("hey",doctopic_triples)



fake_keys_file="/Users/omkarpatil/Downloads/CS249/FakeNews/fake_keys.txt"
real_keys_file="/Users/omkarpatil/Downloads/CS249/FakeNews/real_keys.txt"

list_of_fake_keys = []
list_of_real_keys = []




file_word_list=[]

with open(fake_keys_file) as f:
    lines = f.readlines()
for line in lines:
    list_of_fake_keys.append(line)
    
with open(real_keys_file) as f:
    lines = f.readlines()
for line in lines:
    list_of_real_keys.append(line)



file_path="/Users/omkarpatil/Downloads/CS249/FakeNews/Fake/"


list = range(1,501)
list=sorted(list,key=str)
doc_no=0
for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()
    list_of_fake_keys_count = [0]*20
    list_of_real_keys_count =  [0]*20
    count_words=0
    
    for word in f.split():
    # do something with word
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_fake_keys_count[j]=list_of_fake_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_cover for file "+str(i)+"####")
    
    attr_values=""
    
    for x in range(len(list_of_fake_keys_count)):
        #print("topic_no "+str(x)+" ---- > "+str(list_of_fake_keys_count[x]/count_words))
        attr_values=attr_values+str(list_of_fake_keys_count[x]/count_words)+"\t"
    
    attr_values=attr_values+"\n"
    
    with open('output_fake', 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".txt"+"\t"+attr_values)
        doc_no=doc_no+1

file_path="/Users/omkarpatil/Downloads/CS249/FakeNews/Real/"

doc_no=0


for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()
    list_of_fake_keys_count = [0]*20
    list_of_real_keys_count =  [0]*20
    count_words=0
    
    for word in f.split():
    # do something with word
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_fake_keys_count[j]=list_of_fake_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_cover for file "+str(i)+"####")
    
    attr_values=""
    
    for x in range(len(list_of_fake_keys_count)):
        #print("topic_no "+str(x)+" ---- > "+str(list_of_fake_keys_count[x]/count_words))
        attr_values=attr_values+str(list_of_fake_keys_count[x]/count_words)+"\t"
    
    attr_values=attr_values+"\n"
    
    with open('output_real', 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".txt"+"\t"+attr_values)
        doc_no=doc_no+1

                

