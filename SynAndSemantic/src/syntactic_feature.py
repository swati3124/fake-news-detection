from bllipparser import RerankingParser
import os

import os.path

rrp = RerankingParser.fetch_and_load('WSJ-PTB3', verbose=True)

rrp.set_parser_options(nbest=5)


dir = os.path.dirname(__file__)  # Give path till src
file_path = os.path.join(dir, '../data/Real')
output_file_path = os.path.join(dir, '../data/output_programs_real.csv')


list = range(1,501)
list=sorted(list,key=str)

doc_no=0
for i in list: 
	sum_log_len=0
	sum_len=0
	p_gram=0
   	file_name=file_path+str(i)+".txt"
   	print "current file :- "+file_name

   	with open(file_name) as f:
   		content = f.readlines()
   	for x in content:
   		if(len(x)==1):
   			continue

   		nbest_list = rrp.parse(x.strip(),rerank=False)
   		#print "length of nbest list :- "+str(len(nbest_list))
   		if(len(nbest_list) > 0):

			sum_log_len=sum_log_len+len(x.strip())*nbest_list[0].parser_score
			sum_len=sum_len+len(x.strip())

	pgram_score=sum_log_len/sum_len

	print "program_score for file no :- "+str(i)+".txt.   "+str(pgram_score) +"\n"

	if os.path.isfile(output_file_path):
		os.remove(output_file_path)

	with open(output_file_path, 'a+') as f:
		f.write(file_path+str(i)+".txt"+"\t"+str(pgram_score)+"\n")



file_path = os.path.join(dir, '../data/Fake')
output_file_path = os.path.join(dir, '../data/output_programs_fake.csv')


list = range(1,501)
list=sorted(list,key=str)


doc_no=0
for i in list: 
	sum_log_len=0
	sum_len=0
	p_gram=0
   	file_name=file_path+str(i)+".txt"
   	print "current file :- "+file_name

   	with open(file_name) as f:
   		content = f.readlines()
   	for x in content:
   		if(len(x)==1):
   			continue

   		nbest_list = rrp.parse(x.strip(),rerank=False)
   		#print "length of nbest list :- "+str(len(nbest_list))
   		if(len(nbest_list) > 0):

			sum_log_len=sum_log_len+len(x.strip())*nbest_list[0].parser_score
			sum_len=sum_len+len(x.strip())

	pgram_score=sum_log_len/sum_len

	print "program_score for file no :- "+str(i)+".txt.   "+str(pgram_score) +"\n"

	if os.path.isfile(output_file_path):
		os.remove(output_file_path)

	with open(output_file_path, 'a+') as f:
		f.write(file_path+str(i)+".txt"+"\t"+str(pgram_score)+"\n")


