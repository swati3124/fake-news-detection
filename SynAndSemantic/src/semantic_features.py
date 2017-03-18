
"""
This file is to be run after running mallet commands on console

@author: omkar.patil, swati.arora
"""


import os
import os.path


dir = os.path.dirname(__file__)  # Give path till src
fake_keys_file = os.path.join(dir, '../data/fake_keys.csv')

real_keys_file = os.path.join(dir, '../data/real_keys.csv')


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


# Genrating filenames in order which mallet returns, so feature can be combined directly
list = range(1,501)
list=sorted(list,key=str)
doc_no=0


file_path = os.path.join(dir, '../data/Fake/')
output_file_path = os.path.join(dir, '../data/output_fake.csv')

if os.path.isfile(output_file_path):
    os.remove(output_file_path)
        
for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()
    list_of_fake_keys_count = [0]*20
    count_words=0
    
    for word in f.split():
        word = word.lower()
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_fake_keys_count[j]=list_of_fake_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_proximity for file "+str(i)+"####")
    
    attr_values=[]
    
    for x in range(len(list_of_fake_keys_count)):
        val = float(list_of_fake_keys_count[x])/count_words
        attr_values.append(str(val))

    str_attr = "\t".join(attr_values)
        
    with open(output_file_path, 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".csv"+"\t"+str_attr+"\n")
        doc_no=doc_no+1


doc_no=0


file_path = os.path.join(dir, '../data/Real/')
output_file_path = os.path.join(dir, '../data/output_real.csv')

if os.path.isfile(output_file_path):
    os.remove(output_file_path)

for i in list :
    file_name=file_path+str(i)+".txt"
    f = open(file_name).read()

    list_of_real_keys_count =  [0]*20
    count_words=0
    
    for word in f.split():
        word = word.lower()
        j=0
        for j in range(20):
            if(word in list_of_fake_keys[j]):
                list_of_real_keys_count[j]=list_of_real_keys_count[j]+1
        count_words=count_words+1
    
    print(" ####topic_proximity for file "+str(i)+"####")
    
    attr_values=[]
    
    for x in range(len(list_of_real_keys_count)):
        val = float(list_of_real_keys_count[x])/count_words
        attr_values.append(str(val))
    
    str_attr = "\t".join(attr_values)
    
    with open(output_file_path, 'a+') as f:
        f.write(str(doc_no)+"\t"+file_path+str(i)+".csv"+"\t"+str_attr+"\n")
        doc_no=doc_no+1

