import pandas


def map_to_percent(r):
    return [float(v)/sum(r) for v in r]


train = pandas.read_csv('train.csv')
test = pandas.read_csv('test.csv')


"""
статистика  погибших/выживших  отдельно для мужчин и женщин в каждом классе
"""
print(train.groupby(['Sex', 'Pclass', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')
"""
статистику  по  всем  числовым  полям, отдельно для мужчин и женщин
"""
print(train.groupby(['Sex', 'SibSp', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')
print(train.groupby(['Sex', 'Parch', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')
print(train.groupby(['Sex', 'Ticket', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')
train['Fare'] = train['Fare'].map(lambda fare: float(fare // 150) + 1)
print(train.groupby(['Sex', 'Fare', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')
train['Age'] = train['Age'].map(lambda age: float(age // 10) + 1)
print(train.groupby(['Sex', 'Age', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')

"""
статистика  погибших/выживших  относительно порта посадки
"""
print(train.groupby(['Embarked', 'Survived']).size().unstack().fillna(0).apply(map_to_percent, axis=1), '\n')

"""
Топ 10 популярных имён
"""
print(train.Name.apply(lambda name: name.split(',')[1].split('.')[1].strip()).value_counts()[:10], '\n')

"""
Заполняем отсутствующие значения медианой по столбцу
"""

train.Age = train.Age.fillna(train['Age'].median())
train.Fare = train.Fare.fillna(train['Fare'].median())
train.SibSp = train.SibSp.fillna(train['SibSp'].median())
train.Parch = train.Parch.fillna(train['Parch'].median())

