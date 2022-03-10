import pandas as pd
from sklearn import model_selection, preprocessing, naive_bayes
import numpy as np

train = pd.read_csv('train.csv')
test = pd.read_csv('test.csv')
td = pd.concat([train, test], ignore_index=True, sort=False)

td['Family'] = td.Parch + td.SibSp
td['Is_Alone'] = td.Family == 0
td['Fare_Category'] = td['Fare'].map(lambda x: x // 100 + 1)

td.Embarked.fillna(td.Embarked.mode()[0], inplace=True)
td.Cabin = td.Cabin.fillna('NA')
td['Salutation'] = td.Name.apply(lambda name: name.split(',')[1].split('.')[0].strip())
grp = td.groupby(['Sex', 'Pclass'])
grp.Age.apply(lambda x: x.fillna(x.median()))
td.Age = td.Age.fillna(td['Age'].mean())

td['Age_Group'] = td['Age'].map(lambda age: float(age // 10) + 1)
td['Sex'] = preprocessing.LabelEncoder().fit_transform(td['Sex'])
td['Embarked'] = pd.get_dummies(td.Embarked, prefix="Emb", drop_first=True)

td.drop(['Fare', 'Cabin', 'Name', 'Salutation', 'Ticket', 'Fare_Category',
         'SibSp', 'Parch', 'Age', 'Embarked', 'Family', 'Age_Group'], axis=1, inplace=True)

# Data to be predicted
X_to_be_predicted = td[td.Survived.isnull()]
X_to_be_predicted = X_to_be_predicted.drop(['Survived'], axis=1)

X_test = td.drop("PassengerId", axis=1).copy()

# Training data
train_data = td
train_data = train_data.dropna()
feature_train = train_data['Survived']
label_train = train_data.drop(['Survived'], axis=1)

clf = naive_bayes.GaussianNB()
x_train, x_test, y_train, y_test = model_selection.train_test_split(label_train, feature_train, test_size=0.2)
clf.fit(x_train, np.ravel(y_train))
print("NB Accuracy: " + repr(round(clf.score(x_test, y_test) * 100, 2)) + "%")
result_rf = model_selection.cross_val_score(clf, x_train, y_train, cv=10, scoring='accuracy')
print('The cross validated score for GaussianNB is:', round(result_rf.mean() * 100, 2))
y_pred = model_selection.cross_val_predict(clf, x_train, y_train, cv=10)

result = clf.predict(X_to_be_predicted)
submission = pd.DataFrame({'PassengerId': X_to_be_predicted.PassengerId, 'Survived': result})
submission.Survived = submission.Survived.astype(int)
print(submission.shape)
filename = 'Titanic Predictions.csv'
submission.to_csv(filename, index=False)
print('Saved file: ' + filename)
submission.Survived = submission.Survived.astype(int)

