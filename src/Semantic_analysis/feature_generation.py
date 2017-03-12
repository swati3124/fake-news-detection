# This is to be run after you have run mallet commands
"""
Created on Fri Mar 10 12:10:05 2017

@author: omkar.patil, swati.arora
"""

import numpy as np
#import itertools
#import operator
import os
import os.path


# Need to change it to relative path - Later
fake_keys_file="/Users/swati.arora/Desktop/FakeNews/fake_keys.csv"
real_keys_file="/Users/swati.arora/Desktop/FakeNews/real_keys.csv"

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


# Need to change it to relative path - Later
file_path="/Users/swati.arora/Desktop/FakeNews/Fake/"


list = range(1,501)
list=sorted(list,key=str)
doc_no=0

if os.path.isfile("output_fake.csv"):
    os.remove("output_fake.csv")
        
for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()
    list_of_fake_keys_count = [0]*20
    count_words=0
    
    for word in f.split():
    # do something with word
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_fake_keys_count[j]=list_of_fake_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_cover for file "+str(i)+"####")
    
    attr_values=[]
    
    for x in range(len(list_of_fake_keys_count)):
        #print("topic_no "+str(x)+" ---- > "+str(list_of_fake_keys_count[x]/count_words))
        val = float(list_of_fake_keys_count[x])/count_words
#        print "Value ----->",val
        attr_values.append(str(val))
    

    str_attr = "\t".join(attr_values)
        
    with open('output_fake.csv', 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".csv"+"\t"+str_attr+"\n")
        doc_no=doc_no+1


# Need to change it to relative path - Later
file_path="/Users/swati.arora/Desktop/FakeNews/Real/"

doc_no=0

if os.path.isfile("output_real.csv"):
    os.remove("output_real.csv")

for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()

    list_of_real_keys_count =  [0]*20
    count_words=0
    
    
    
    for word in f.split():
    # do something with word
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_real_keys_count[j]=list_of_real_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_cover for file "+str(i)+"####")
    
    attr_values=[]
    
    for x in range(len(list_of_real_keys_count)):
        #print("topic_no "+str(x)+" ---- > "+str(list_of_real_keys_count[x]/count_words))
        val = float(list_of_real_keys_count[x])/count_words
        attr_values.append(str(val))
    
    str_attr = "\t".join(attr_values)
    
    with open('output_real.csv', 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".csv"+"\t"+str_attr+"\n")
        doc_no=doc_no+1

                

