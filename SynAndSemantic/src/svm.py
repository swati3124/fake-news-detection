# -*- coding: utf-8 -*-
"""

@author: swati.arora
"""


from sklearn.svm import SVC
from sklearn import metrics
from sklearn.metrics import confusion_matrix, classification_report, roc_curve, accuracy_score
import pandas as pd
import numpy as np
from sklearn import cross_validation  
import matplotlib.pyplot as plt
import os
import os.path

dir = os.path.dirname(__file__)  # Give path till src

file_path = os.path.join(dir, '../data/fake_composition.csv')
fake_feature1 = pd.read_csv(file_path, sep='\t', header=None)

file_path = os.path.join(dir, '../data/real_composition.csv')
real_feature1 = pd.read_csv(file_path,  sep='\t', header=None)

file_path = os.path.join(dir, '../data/output_fake.csv')
fake_feature2 = pd.read_csv(file_path, sep='\t', header=None)

file_path = os.path.join(dir, '../data/output_real.csv')
real_feature2 = pd.read_csv(file_path,  sep='\t', header=None)

file_path = os.path.join(dir, '../data/output_programs_fake.csv')
fake_feature_syn = pd.read_csv(file_path, sep='\t', header=None)

file_path = os.path.join(dir, '../data/output_programs_real.csv')
real_feature_syn = pd.read_csv(file_path, sep='\t', header=None)

fake_x1 = fake_feature1.iloc[:,2:]
fake_y = pd.DataFrame(np.zeros((500,1)))
real_x1 = real_feature1.iloc[:,2:]
real_y = pd.DataFrame(np.ones((500,1)))

fake_x2 = fake_feature2.iloc[:,2:]
real_x2 = real_feature2.iloc[:,2:]

fake_x3 = fake_feature_syn.iloc[:,1:]
real_x3 = real_feature_syn.iloc[:,1:]

df_fake = [fake_x1, fake_x2, fake_x3]
fake_x = pd.concat(df_fake, axis = 1)

df_real = [real_x1, real_x2, real_x3]
real_x = pd.concat(df_real, axis = 1)


feature_matrix = fake_x.append(real_x, ignore_index=True)
label_matrix = fake_y.append(real_y, ignore_index=True)

total_error = 0
#SVM classification
for i in range(10):
    X_train,X_test, Y_train, Y_test =  cross_validation.train_test_split(feature_matrix, label_matrix, test_size=0.1, random_state=42)
    svc_classifier = SVC(kernel = 'linear', probability=True)
    fit_model = svc_classifier.fit(X_train, Y_train)
    Y_predicted = fit_model.predict(X_test)
    mse = metrics.mean_squared_error(Y_test, Y_predicted)
    error = Y_predicted.reshape(100,1) - Y_test
    total_error += np.dot(np.transpose(error),error)

# Metrics for model    
rmse_10fold = np.sqrt(total_error/len(feature_matrix))
print "rmse:", rmse_10fold

print "Confusion matrix \n"
print confusion_matrix(Y_test, Y_predicted) 
print "\n"

print "Recall and Precision score \n"
print classification_report(Y_test, Y_predicted)
print "\n"

accu = accuracy_score(Y_test, Y_predicted)
print "\nAccuracy : ", (accu*100)

#ROC curve
probas_ = fit_model.predict_proba(X_test)                                    
fpr_svc, tpr_svc, thresholds = roc_curve(Y_test, probas_[:, 1])
plt.plot(fpr_svc, tpr_svc, lw=1, color='red', label='ROC curve')
plt.plot([0, 1], [0, 1], color='navy', lw=1, linestyle='--')
plt.xlim([-0.05, 1.05])
plt.ylim([-0.05, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('SVM ROC Curve')
plt.legend(loc="lower right")
plt.show()