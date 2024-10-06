# 基于Python的数据分析

## 实验目的

熟悉基于 python 的数据分析基本操作：包括 NumPy 的 ndarray 对象 的向量和矩阵操作，pandas 的输入导入和基于 DateFrame 对象， sklearn 中数据和算法调用，以及基于 matplotlib 的画图。

## 实验内容

### 1、基于 numpy 中 ndarray 对象基本操作

#### 1.1 创建向量 v= [48, 6, 51, 32, 4, 85]，并转成 ndarray 对象类型；

In [2]:

```
import numpy as np
v = np.array([48,6,51,32,4,85])
v = v.reshape(1,6)
print(v)
[[48  6 51 32  4 85]]
```

#### 1.2 查看向量 v 的形状、数据类型；

In [3]:

```
print(v.shape)
print(v.dtype)
(1, 6)
int32
```

#### 1.3 将向量 v 转成浮点数向量，并查看向量 v 的形状、数据类型；

In [4]:

```
v = np.array(v, dtype = float)
print (v.shape)
print (v.dtype)
(1, 6)
float64
```

#### 1.4 对向量 v 前三项求和、后四项的平方求均值；

In [5]:

```
print(np.sum(v[:,:3]))
105.0
```

In [6]:

```
print(np.sum(v[:,-4:]**2)/4)
2716.5
```

#### 1.5 向量 v 的奇数项（第一项下标为 0）变成原来的算术平方根；

In [7]:

```
i = 1
while i < 6:
    v[0, i] = np.sqrt(v[0, i])
    i += 2
print(v)
[[48.          2.44948974 51.          5.65685425  4.          9.21954446]]
```

#### 1.6 求向量 v 最小、最大值及其所在位置（打印下标）；

In [8]:

```
max = v.max()
min = v.min()
i = 0
while i < 6:
    if v[0, i] == max:
        print('最大值位置在第', i, '个')
    if v[0, i] == min:
        print('最小值位置在第', i, '个')
    i += 1
最小值位置在第 1 个
最大值位置在第 2 个
```

#### 1.7 对向量 v 排序，并输出排序后的向量以及排序前的索引。

In [9]:

```
print(np.sort(v))
print(np.argsort(v))
[[ 2.44948974  4.          5.65685425  9.21954446 48.         51.        ]]
[[1 4 3 5 0 2]]
```

#### 1.8 创建矩阵 M，并转成 ndarray 对象类型:

[ [45,62,31,753], [78,43,12,546], [146,785,2475,7] ]

In [10]:

```
import numpy as np
M = np.array([ [45,62,31,753], [78,43,12,546], [146,785,2475,7] ])
print(M)
[[  45   62   31  753]
 [  78   43   12  546]
 [ 146  785 2475    7]]
```

#### 1.9 查看矩阵 M 的形状、数据类型；

In [11]:

```
print(M.shape)
print(M.dtype)
(3, 4)
int32
```

#### 1.10 将矩阵 M 转成浮点数矩阵，并查看矩阵 m 的形状、数据类型；

In [12]:

```
M = np.array(M, dtype = float)
print (M.shape)
print (M.dtype)
(3, 4)
float64
```

#### 1.11 矩阵 M 按列、行求和；

In [13]:

```
print(np.sum(M, axis = 0))  # 按列 
print(np.sum(M, axis = 1))  # 按行
[ 269.  890. 2518. 1306.]
[ 891.  679. 3413.]
```

#### 1.12 对矩阵 M 的第 0 行和第 1 行求欧式距离（基于 numpy 向量化运算）；

In [14]:

```
vec1 = M[0,:]
vec2 = M[1,:]
d=np.sqrt(np.sum(np.square(vec1-vec2)))
print(d)
211.32912719263285
```

#### 1.13 调用 np.linalg.norm 实现 6)中计算，对比结果。

In [15]:

```
D = np.linalg.norm(vec1 - vec2)
print(D)  # 结果相同
211.32912719263285
```

#### 1.14 把矩阵 M 的每一行归一化为单位向量,即向量长度（模）为 1，并打印确认。

In [34]:

```
for i in range(3):
    for k in M[i,]:
        M[i,j]=k/np.sqrt(np.sum(M[i,:]**2))
print(M)
[[4.50000000e+01 6.20000000e+01 9.94864431e-01 7.53000000e+02]
 [7.80000000e+01 4.30000000e+01 9.86954565e-01 5.46000000e+02]
 [1.46000000e+02 7.85000000e+02 8.76652128e-03 7.00000000e+00]]
```

#### 1.15 计算 M 中每两行之间的相似度矩阵 S

In [35]:

```
MM = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
for i in range(3):
    a = M[i,:]
    for j in range(3):
        b = M[2 - j,:]
        MM[i][j] = a.dot(b)
print(MM)
[[60511.008721500206, 417314.981885992, 572878.9897552358], [48965.008652158205, 306049.9740793141, 417314.981885992], [637590.0000768519, 48965.008652158205, 60511.008721500206]]
```

### 2、基于 pandas 对象 DataFrame 的基本操作

#### 2.1 用 pandas 读取 flights.csv 文件保存为 df，并打印前 5 行。

In [2]:

```
import pandas as pd
df = pd.read_csv(r"D:\编程\阿伟的笔记本\大二下\数据挖掘\作业\flights.csv")  # 一定要加"r"
print(df[:5])
   year  month  day  dep_time  dep_delay  arr_time  arr_delay carrier tailnum  \
0  2013      1    1     517.0        2.0     830.0       11.0      UA  N14228   
1  2013      1    1     533.0        4.0     850.0       20.0      UA  N24211   
2  2013      1    1     542.0        2.0     923.0       33.0      AA  N619AA   
3  2013      1    1     554.0       -6.0     812.0      -25.0      DL  N668DN   
4  2013      1    1     554.0       -4.0     740.0       12.0      UA  N39463   

   flight origin dest  air_time  distance  hour  minute  
0    1545    EWR  IAH     227.0      1400   5.0    17.0  
1    1714    LGA  IAH     227.0      1416   5.0    33.0  
2    1141    JFK  MIA     160.0      1089   5.0    42.0  
3     461    LGA  ATL     116.0       762   5.0    54.0  
4    1696    EWR  ORD     150.0       719   5.0    54.0  
```

#### 2.2 用.info()方法查看数据基本统计信息，观察每个特征的是否存在缺失值。

In [3]:

```
print(df.info(verbose=True))
<class 'pandas.core.frame.DataFrame'>
RangeIndex: 160754 entries, 0 to 160753
Data columns (total 16 columns):
 #   Column     Non-Null Count   Dtype  
---  ------     --------------   -----  
 0   year       160754 non-null  int64  
 1   month      160754 non-null  int64  
 2   day        160754 non-null  int64  
 3   dep_time   158418 non-null  float64
 4   dep_delay  158418 non-null  float64
 5   arr_time   158275 non-null  float64
 6   arr_delay  157927 non-null  float64
 7   carrier    160754 non-null  object 
 8   tailnum    159321 non-null  object 
 9   flight     160754 non-null  int64  
 10  origin     160754 non-null  object 
 11  dest       160754 non-null  object 
 12  air_time   157927 non-null  float64
 13  distance   160754 non-null  int64  
 14  hour       158418 non-null  float64
 15  minute     158418 non-null  float64
dtypes: float64(7), int64(5), object(4)
memory usage: 19.6+ MB
None
```

#### 2.3 输出存在缺失值的前 3 个记录（一行为一个记录）。

In [4]:

```
n = 3
i = 0
while n:
    if df.iloc[i].isnull().any():
        print(df.iloc[i])
        print()
        n = n - 1
    i = i + 1
year           2013
month             1
day               1
dep_time     1807.0
dep_delay      29.0
arr_time     2251.0
arr_delay       NaN
carrier          UA
tailnum      N31412
flight         1228
origin          EWR
dest            SAN
air_time        NaN
distance       2425
hour           18.0
minute          7.0
Name: 330, dtype: object

year           2013
month             1
day               1
dep_time        NaN
dep_delay       NaN
arr_time        NaN
arr_delay       NaN
carrier          AA
tailnum      N3EHAA
flight          791
origin          LGA
dest            DFW
air_time        NaN
distance       1389
hour            NaN
minute          NaN
Name: 403, dtype: object

year           2013
month             1
day               1
dep_time        NaN
dep_delay       NaN
arr_time        NaN
arr_delay       NaN
carrier          AA
tailnum      N3EVAA
flight         1925
origin          LGA
dest            MIA
air_time        NaN
distance       1096
hour            NaN
minute          NaN
Name: 404, dtype: object
```

#### 2.4 计算每个属性的缺失率，即该属性值缺失的记录数与总记录数的百分比，并输出缺失率最大的 3 个属性及其缺失率。

In [38]:

```
alist = ["year", "month", "day", "dep_time", "dep_delay", "arr_time", "arr_delay", "carrier", "tailnum", "flight", "origin", "dest", "air_time", "distance", "hour", "minute"]
bdict = dict()
for i in alist:
    a = df[i].isnull().sum()/(df[i].isnull().sum() + df[i].notnull().sum())
    bdict[i] = a
    print(i, '{:.2%}'.format(a))
print("\n缺失率最大的 3 个属性及其缺失率:")
bdict = sorted(bdict.items(), key = lambda x : x[1], reverse = True)
j = 3
for i in bdict:
    print(i[0], '{:.2%}'.format(i[1]))
    j = j - 1
    if j == 0:
        break
year 0.00%
month 0.00%
day 0.00%
dep_time 1.45%
dep_delay 1.45%
arr_time 1.54%
arr_delay 1.76%
carrier 0.00%
tailnum 0.89%
flight 0.00%
origin 0.00%
dest 0.00%
air_time 1.76%
distance 0.00%
hour 1.45%
minute 1.45%

缺失率最大的 3 个属性及其缺失率:
arr_delay 1.76%
air_time 1.76%
arr_time 1.54%
```

#### 2.5 用 0 填充 df 所有的缺失值，并验证 df 是否还存在缺失值。

In [43]:

```
df = df.fillna(0)
print(df.isnull().sum())
# 运行结果可验证不存在缺失值了
year         0
month        0
day          0
dep_time     0
dep_delay    0
arr_time     0
arr_delay    0
carrier      0
tailnum      0
flight       0
origin       0
dest         0
air_time     0
distance     0
hour         0
minute       0
dtype: int64
```

#### 2.6 求 df 每个数值列的均值并输出。

In [65]:

```
alist = ["year", "month", "day", "dep_time", "dep_delay", "arr_time", "arr_delay", "flight", "air_time", "distance", "hour", "minute"]
for i in alist:
    print(i, df[i].mean())
year 2013.0
month 6.547395399181358
day 15.71656692835015
dep_time 1297.0204038468717
dep_delay 9.326250046655138
arr_time 1494.0701195615661
arr_delay 2.057703074262538
flight 1156.344986749941
air_time 177.50765144257684
distance 1282.4454197096184
hour 12.651032011645123
minute 31.91720268235938
```

#### 2.7 输出 hour 列的中位数

In [45]:

```
print(df["hour"].median())
13.0
```

#### 2.8 统计 flights 的特征 distance 在区间[0, 100)、[100, 200)、[200, 500)、[500, 1000)、[1000, 2000)、[2000, 5000)的样本数量，绘制直方图figure 1。

In [64]:

```
import matplotlib.pyplot as plt
x = ["[0,100)", "[100,200)", "[200,500)", "[500,1000)", "[1000,2000)", "[2000,5000)"]
y = [0, 0, 0, 0, 0, 0]
for i in df["flight"]:
    if 0 <= i < 100:
        y[0] += 1
    elif 100 <= i < 200:
        y[1] += 1
    elif 200 <= i < 500:
        y[2] += 1
    elif 500 <= i < 1000:
        y[3] += 1
    elif 1000 <= i < 2000:
        y[4] += 1
    elif 2000 <= i < 5000:
        y[5] += 1
plt.figure(figsize=(8, 6))
xs = range(len(x))
plt.bar(xs, y)
plt.xticks(xs, x)
plt.title("flight")
plt.show()
x = ["[0,100)", "[100,200)", "[200,500)", "[500,1000)", "[1000,2000)", "[2000,5000)"]
y = [0, 0, 0, 0, 0, 0]
for i in df["distance"]:
    if 0 <= i < 100:
        y[0] += 1
    elif 100 <= i < 200:
        y[1] += 1
    elif 200 <= i < 500:
        y[2] += 1
    elif 500 <= i < 1000:
        y[3] += 1
    elif 1000 <= i < 2000:
        y[4] += 1
    elif 2000 <= i < 5000:
        y[5] += 1
plt.figure(figsize=(8, 6))
xs = range(len(x))
plt.bar(xs, y)
plt.xticks(xs, x)
plt.title("distance")
plt.show()
```

![img](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAArYAAAIOCAYAAABNmk70AAAAOXRFWHRTb2Z0d2FyZQBNYXRwbG90bGliIHZlcnNpb24zLjUuMiwgaHR0cHM6Ly9tYXRwbG90bGliLm9yZy8qNh9FAAAACXBIWXMAAA9hAAAPYQGoP6dpAAA980lEQVR4nO3dfXRU1b3/8U+ahzEJyQjEJE6Nyr1NERq0GDUE2oIFEiwh7bIt2ugUKg30osRUslCutqK9BgUEWlO9yOWCBWzailSXSAxcFUsJD6bklgBaH3gINSEowwQwTtK4f3/0x7lOEh4m5IFs36+1zlrOOd85e5+9meHD9uQkzBhjBAAAAPRyX+jpDgAAAACdgWALAAAAKxBsAQAAYAWCLQAAAKxAsAUAAIAVCLYAAACwAsEWAAAAViDYAgAAwAoEWwAAAFiBYAsAF4Df/e53+spXvqLo6GiFhYXpO9/5jsLCwoJqRo0apVGjRnXo/JMnT1afPn3OWvfxxx9rzpw5ev311zvUDgD0pIie7gAAfN4dOXJEXq9X48aN05NPPimXy6Xnn3++Td2TTz7Z5X35+OOP9dBDD0lSh0M0APQUgi0A9LC//e1vam5u1u23366RI0dKksrKytrUDR48uLu7BgC9CrciAEAPmjx5sr72ta9Jkm655RaFhYWddqW0vVsRDh06pO9973uKi4vTxRdfrNtuu007duxQWFiYVqxY0eYc7777rr71rW+pT58+SklJ0cyZMxUIBCRJ+/fv1yWXXCJJeuihhxQWFqawsDBNnjy5sy4XALoUwRYAetDPfvYz/frXv5YkFRcXq6Ki4pxvOTh58qRuvPFGvfbaa3rsscf0+9//XklJSbrlllvarW9ublZubq5Gjx6tF154QXfccYcWLVqkxx57TJJ06aWXOivFU6ZMUUVFhSoqKvSzn/2sE64UALoetyIAQA/613/9V+cWg9TUVA0bNuyc3/vMM8/o3Xff1fr16zVu3DhJUlZWlj7++GMtWbKkTX1TU5Meeughff/735ckjR49Wm+++aaeffZZ/fznP5fL5VJ6erok6bLLLgupLwBwIWDFFgB6qU2bNikuLs4Jtaf84Ac/aLc+LCxMEyZMCNp39dVX68CBA13WRwDoTgRbAOilPvroIyUlJbXZ394+SYqJidFFF10UtM/lcumTTz7pkv4BQHcj2AJAL9W/f38dPny4zf66uroe6A0A9DyCLQD0UiNHjtTx48e1fv36oP2lpaUdPqfL5ZIkNTY2nlffAKAnEGwBoJeaNGmSvvSlL+n222/XU089pQ0bNuiee+7RK6+8Ikn6whdC/4qPi4vTFVdcoRdeeEHl5eV68803tX///k7uOQB0DYItAPRSsbGxevXVVzVq1CjNmjVL3/3ud3Xw4EHncWEXX3xxh867bNkyxcTEKDc3V9dff73mzJnTeZ0GgC4UZowxPd0JAEDnKS4u1gMPPKCDBw/qsssu6+nuAEC34Tm2ANCLlZSUSJKuuuoqNTc369VXX9WvfvUr3X777YRaAJ87BFsA6MViYmK0aNEi7d+/X4FAQJdffrnuvfdePfDAAz3dNQDodtyKAAAAACvww2MAAACwQkjB9sorr1RYWFib7c4775QkGWM0Z84ceTweRUdHa9SoUdq9e3fQOQKBgGbMmKGEhATFxsYqNzdXhw4dCqrx+Xzyer1yu91yu93yer06duxYUM3Bgwc1YcIExcbGKiEhQQUFBWpqaurAEAAAAMAGIQXbHTt2qLa21tk2bNggSfr+978vSZo3b54WLlyokpIS7dixQ8nJyRo7dqyOHz/unKOwsFBr165VaWmpNm/erBMnTignJ0ctLS1OTV5enqqqqlRWVqaysjJVVVXJ6/U6x1taWjR+/HidPHlSmzdvVmlpqdasWaOZM2ee12AAAACg9zqve2wLCwv10ksv6Z133pEkeTweFRYW6t5775X0z9XZpKQkPfbYY5o2bZr8fr8uueQSrVy5Urfccosk6YMPPlBKSopefvllZWdna+/evRo8eLC2bt2qjIwMSdLWrVuVmZmpt956SwMHDtT69euVk5OjmpoaeTweSf/8TTuTJ09WfX294uPjz6n/n376qT744APFxcUpLCyso8MAAACALmKM0fHjx+XxeM7+i2dMBwUCAdO/f3/zyCOPGGOMee+994wk85e//CWoLjc31/zwhz80xhjzP//zP0aSOXr0aFDN1VdfbX7+858bY4xZtmyZcbvdbdpzu93mv//7v40xxvzsZz8zV199ddDxo0ePGknm1VdfPW2fP/nkE+P3+51tz549RhIbGxsbGxsbG9sFvtXU1Jw1n3b4cV9//OMfdezYMU2ePFmSVFdXJ0lKSkoKqktKStKBAwecmqioKPXt27dN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TFVVVT3dnbN66aWXNHToUH366ac93ZVz0tvGt7MUFRWpoKCgp7vhYB661+d1vM/F9773PS1cuLDTz8uYn5/rr79ezz///Hmdgzk4P50xB13GoNcYOXKkyc/PN7W1taa5udkYY8yBAwdMTk6OiYmJMf379zczZswwgUDgjOdZsmSJGTlypImLizOSjM/na1Nz9OhRc/vtt5v4+HgTHx9vbr/99jZ159L20KFDzcqVK8/rurtLe+NbUFBgrr32WhMVFWWuueaadt/317/+1XzjG98wF110kfF4POahhx4yn376aVDN66+/bq699lrjcrnMgAEDzFNPPXXGvlRVVZlbb73VXHbZZeaiiy4yV111lVm8eHGXtH348GHTp08f8/77759tiLpF63nozrFoj6Q2W+v39eZ5aO/PfXddc3u68zP33HPPmUGDBpmoqCgzaNAg8/zzzwcd/9///V/Tr18/4/f7z9rvUPT0d83Zrru11157zeTm5prk5GQTExNjrrnmGrNq1ao2dZ3V9q9//Wtz5ZVXGpfLZa699lrzxhtvBB1/4YUXTGpqqmlpaTljv8+kp79nQp2Dffv2tfu5XL9+fZe03R1z0FUItr3IyJEjzd133+28/sc//mHS0tLMjTfeaP7yl7+YDRs2GI/HY+66664znmfRokVm7ty5Zu7cuacNtuPGjTNpaWlmy5YtZsuWLSYtLc3k5OSE3PavfvUrc8MNN5zXdXeX1uNrjDEzZswwJSUlxuv1tvuXjd/vN0lJSebWW281u3btMmvWrDFxcXFmwYIFTs37779vYmJizN1332327Nljli5daiIjI81zzz132r4sW7bMzJgxw7z++uvmvffeMytXrjTR0dHmiSee6JK2b775ZjNr1qwQR6xrtJ6H7h6L1iSZ5cuXm9raWmf7+OOPu6TtnpiH9v7cd+c1t9Zdn7ktW7aY8PBwU1xcbPbu3WuKi4tNRESE2bp1a1B71157rXnyySfPZSjPWU9+15zrdX/WI488Yh544AHz5z//2bz77rvml7/8pfnCF75gXnzxxU5vu7S01ERGRpqlS5eaPXv2mLvvvtvExsaaAwcOODX/+Mc/TGJionn55ZfPabzb05PfMx2Zg1PBduPGjUGfy88uJvW2OegqBNtepPUH8eWXXzZf+MIXzN///ndn329/+1vjcrnOaYXhtddeazfY7tmzx0gK+oNeUVFhJJm33norpLb3799vJJn33nsv1Mvtdu39ZXPKgw8+2O5fNk8++aRxu93mk08+cfbNnTvXeDwe51/xs2bNMldddVXQ+6ZNm2aGDRsWUv+mT59ubrzxxi5pe8WKFSYlJSWk/nSVM83DKV05Fq1JMmvXrj3t8d4+D6cLtt11zafT1Z+5iRMnmnHjxgXVZGdnm1tvvTVo35w5c8zXv/71c+rzuerJ75pzve6z+da3vmV+9KMfOa87q+0bbrjB/OQnPwmqueqqq8x9990XtG/y5MnG6/WG1OfP6snvmY7Mwalgu3PnztPW9LY56CrcY9uLVVRUKC0tTR6Px9mXnZ2tQCCgysrK8zqv2+1WRkaGs2/YsGFyu93asmVLSG1fccUVSkxM1J/+9KcO9+dCVlFRoZEjRwY9QDs7O1sffPCB9u/f79RkZWUFvS87O1tvvvmmmpubz7ktv9+vfv36dUnbN9xwg2pqanTgwIFz7k9P6sqxaM9dd92lhIQEXX/99frP//zPoPvGbZ2H7rrmUHVW26erOfUdd8oNN9yg7du3KxAIdLjPnaG7r/ts2vsMnm/bTU1NqqysbFOTlZXV7rx09d8rXfU9cz5zkJubq8TERI0YMULPPfdc0DEb56AjCLa9WF1dnZKSkoL29e3bV1FRUaqrqzuv8yYmJrbZn5iY6Jw3lLa/+MUvOh9627Q3Dqden2mskpKS9I9//EMffvjhObVTUVGh3//+95o2bVqXtP3FL35RknrFPHX1WLT2i1/8Qn/4wx+0ceNG3XrrrZo5c6aKi4u7pO0LZR6685pD1Vltn66mve+vQCBwXt+pnaG7r/tMnnvuOe3YsUM/+tGPztq/UNr+8MMP1dLScs7zcvDgwS774eSu/J7pyBz06dNHCxcu1HPPPaeXX35Zo0eP1i233KJVq1adtX+9dQ46qlf/Sl1IYWFhbfYZY9rd39nnPde2o6Oj9fHHH59Xfy5kra/X/P9f5nemsWqv5nR2796tb3/72/r5z3+usWPHdknb0dHRknTBz1N3jEVrDzzwgPPfX/3qVyVJDz/8cNB+2+ahO6+5Izqr7fZq2vv+knp+TqTuve7Tef311zV58mQtXbpUX/nKVzqlf633neu8fPrppwoEAs4cdZbu+J4JdQ4SEhL005/+1Hl93XXXyefzad68ebr99ts7ve2enoPzwYptL5acnNzmX1A+n0/Nzc1t/rUV6nkPHz7cZv+RI0ec84bS9tGjR3XJJZd0uD8XsvbGob6+XpLOOFb19fWKiIhQ//79z3j+PXv26Jvf/Kby8/ODQkVnt3306FFJuqDnqbvG4myGDRumhoYG5zPyeZiHrrzmUHVW26erae/7S+r5Oenu627Ppk2bNGHCBC1cuFA//OEPz6l/obSdkJCg8PDwc56XmJiYTg9U3fE9cz5z8FnDhg3TO++8c9b+9bY5OF8E214sMzNT1dXVqq2tdfaVl5fL5XIpPT39vM7r9/u1fft2Z9+2bdvk9/s1fPjwkNr+5JNP9N5772no0KEd7s+FLDMzU2+88YaampqcfeXl5fJ4PLryyiudmg0bNgS9r7y8XNddd50iIyNPe+7du3frxhtv1KRJk/TII490advV1dWKjIxsswJzoejOsTibnTt36qKLLtLFF1/c6W1fqPPQldccqs5q+3Q1p77jTqmurtZll12mhISEDve5M3T3dbf2+uuva/z48Xr00Uc1derUdvt3vm1HRUUpPT29Tc2GDRvanZdrr732jH0OVXd9z3R0DlrbuXOnLr300qD+9fY56BTd8zNq6Ayne9zX6NGjzV/+8hezceNGc9lll531cV+1tbVm586dZunSpUaSeeONN8zOnTvNRx995NSMGzfOXH311aaiosJUVFSYIUOGtPu4r7O1/dprr5k+ffqYkydPds4gdKH2fkr2nXfeMTt37jTTpk0zX/7yl83OnTvNzp07nUesHDt2zCQlJZkf/OAHZteuXeb555838fHx7T7+5ac//anZs2ePWbZs2Vkfe1RdXW0uueQSc9tttwU92qW+vt6p6cy2H3zwQfPNb37zfIav07Seh+4ei8968cUXzdNPP2127dpl3n33XbN06VITHx9vCgoKuqTtnpiH1uPd3dfcWnd95v785z+b8PBw8+ijj5q9e/eaRx99tN1HLk2aNMnccccdHRrb0+nJ75pzve7Peu2110xMTIyZPXt20Gfws39ndFbbpx41tWzZMrNnzx5TWFhoYmNjzf79+9uM4cMPPxzawLd6f099z3RkDlasWGFWr15t9uzZY9566y0zf/58ExkZaRYuXNjpbXfXHHQVgm0v0t6X4YEDB8z48eNNdHS06devn7nrrruCHkVizP89k/KUBx98sN0HPX+25qOPPjK33XabiYuLM3Fxcea2225r9xc0nK3tqVOnmmnTpnXG5Xe59sZ35MiR7Y7Vvn37nJq//vWv5utf/7pxuVwmOTnZzJkzp90Hdg8dOtRERUWZK6+8ss1Ds089eu3UeU83R1dccUXQ+zqjbWOM+fKXv2x++9vfhjZgXaT1PHTnWLSeh/Xr15uvfvWrpk+fPiYmJsakpaWZxYsXOw/V78y2jemZeWg93t15za3H+1R/uuMzZ4wxf/jDH8zAgQNNZGSkueqqq8yaNWuCjjc2Npr4+HhTUVFxLkN5znryu8aYs1/38uXLzWfXvSZNmtRu30aOHNnpbRvzz18OcMUVV5ioqChz7bXXmk2bNgUdP3TokImMjDQ1NTVt3nuuevJ75lzGofUcrFixwgwaNMjExMSYuLg4k56e3u4vP+pNc9BVCLa9yLk8d6+1ffv2mYiICPO3v/2tazp1BvX19aZfv34XzG+0OpuOjG9nWb58ufnSl75kmpqaur3tl156yQwaNKhNcOkpzEP3zsPndbzPRUlJiRk7dmynn7cnx/xcPPjgg21C64WkqKjI5Ofnn9c5mIPz0xlz0FW4x7aXefLJJ9WnTx/t2rXrnOrLyso0depUpaamdnHP2tq3b5+efPJJDRgwoNvb7qhQx7ezlJWVqbi4+LzuPeyokydPavny5YqIuHAeksI8dK/P43ifi8jISD3xxBNdcu6eGvNz8corr2jevHk93Y3TSkxM1C9+8YvzPg9z0HGdNQddIcyY//8sCFzw/v73v6uxsVGSdPnllysqKqqHe2QXxvfCwDx0L8a7+zHmPY85sBfBFgAAAFbgVgQAAABYgWALAAAAKxBsAQAAYAWCLQAAAKxAsAUAAIAVCLYAAACwAsEWAAAAViDYAgAAwAoEWwAAAFjh/wHT2d892R9qfQAAAABJRU5ErkJggg== )

![img](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAArYAAAIOCAYAAABNmk70AAAAOXRFWHRTb2Z0d2FyZQBNYXRwbG90bGliIHZlcnNpb24zLjUuMiwgaHR0cHM6Ly9tYXRwbG90bGliLm9yZy8qNh9FAAAACXBIWXMAAA9hAAAPYQGoP6dpAAA8n0lEQVR4nO3dfXRU1b3/8U/Mw5CEZEyIyZiaIl2NERpUDBoCVVAgQQl4l+1VG02h0oBFianJpXJ1VdQaEBCxUi1yWWIFTVuR1orGwFVRSngwJZYIWq0IURNAGSZAYxLD/v3RH+c6SXiYEDJk836tNWt1zvmes/fZuzN83OvkTIgxxggAAADo4c4KdgcAAACArkCwBQAAgBUItgAAALACwRYAAABWINgCAADACgRbAAAAWIFgCwAAACsQbAEAAGAFgi0AAACsQLAFgG4wc+ZMhYSEOO/PP/98TZw4MaBzrF+/XjNnztT+/fu7tnMAYImwYHcAAM5EK1euVGxsbEDHrF+/Xvfff78mTpyos88++9R0DAB6MIItAATBoEGDgt0FALAOtyIAQBdbtWqVLrnkErlcLvXr10/z5s1rV9P2VoTDhw/rV7/6ldLS0hQZGamzzz5bF110kR577DFJ/76V4b/+678kSf369VNISIhCQkL05ptvSpJ+//vfKzs7W+eee64iIyPVv39/3X333Tp06JBfuxMnTlTv3r310Ucf6dprr1Xv3r2VkpKi4uJiNTU1+dU2NTXpgQceUP/+/dWrVy/16dNHV111ldavX+/UGGP0xBNP6JJLLlFkZKTi4uL0wx/+UB9//HFXDCUABIQVWwDoQv/7v/+r6667TllZWSorK1Nra6vmzJmj3bt3H/O4OXPmaObMmbr33nt15ZVXqqWlRe+//75zP+1Pf/pT7du3T48//rhefPFFnXvuuZKkAQMGSJI+/PBDXXvttSoqKlJ0dLTef/99Pfzww9q0aZNef/11v7ZaWlo0fvx4TZo0ScXFxXrrrbf04IMPyu1265e//KUk6euvv9Y111yjt99+W0VFRbr66qv19ddfa8OGDdq1a5eGDh0qSZoyZYqWLl2qwsJCPfzww9q3b58eeOABDR06VO+++66SkpK6cngB4NgMAKDLZGZmmuTkZNPY2Ohsa2hoMPHx8eabX7l9+/Y1EyZMcN7n5uaaSy655Jjnnjt3rpFkduzYccy6w4cPm5aWFrN27Vojybz77rvOvgkTJhhJ5g9/+IPfMddee61JS0tz3v/ud78zkszixYuP2k5lZaWRZB555BG/7bW1tSYyMtJMnz79mP0EgK7GrQgA0EUOHTqkzZs36/rrr1evXr2c7TExMRo3btwxj7388sv17rvvaurUqXrttdfU0NAQUNsff/yx8vLy5PF4FBoaqvDwcA0fPlyStH37dr/akJCQdv256KKLtHPnTuf9q6++ql69eunWW289apsvv/yyQkJCdMstt+jrr792Xh6PRxdffLFzmwQAdBduRQCALuL1enX48GF5PJ52+zra9k0zZsxQdHS0li1bpt/+9rcKDQ3VlVdeqYcffliDBw8+5rEHDx7UFVdcoV69eulXv/qVLrjgAkVFRam2tlbXX3+9Ghsb/eqjoqL8grckuVwuffXVV877vXv3Kjk5WWeddfT1j927d8sYc9TbDb7zne8cs98A0NUItgDQReLi4hQSEqL6+vp2+zra9k1hYWG66667dNddd2n//v1as2aN/vu//1s5OTmqra1VVFTUUY99/fXX9fnnn+vNN990VmklndTzbs855xytW7dOhw8fPmq4TUhIUEhIiN5++225XK52+zvaBgCnErciAEAXiY6O1uWXX64XX3zRb/XzwIED+stf/nLC5zn77LP1wx/+ULfffrv27dunTz75RNL/BcW2K7BHfvihbZBctGhRZy5DknTNNdfoq6++0tKlS49ak5ubK2OMPvvsMw0ePLjda+DAgZ1uHwA6gxVbAOhCDz74oMaMGaPRo0eruLhYra2tevjhhxUdHa19+/Yd9bhx48YpPT1dgwcP1jnnnKOdO3dqwYIF6tu3r1JTUyXJCYqPPfaYJkyYoPDwcKWlpWno0KGKi4vTbbfdpvvuu0/h4eFavny53n333U5fx49+9CM9/fTTuu222/TBBx/oqquu0uHDh7Vx40b1799fN910k4YNG6bJkyfrJz/5id555x1deeWVio6OVl1dndatW6eBAwfqZz/7Waf7AACBYsUWALrQ6NGj9ac//UkNDQ268cYbddddd+kHP/jBMf8IS5KuuuoqvfXWW7rttts0evRo3XvvvRo5cqTWrl2r8PBwSdKIESM0Y8YM/eUvf9H3v/99XXbZZaqqqlKfPn20atUqRUVF6ZZbbtGtt96q3r176/e/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xRf99r/77rsmPj7e+Hy+4/Y7EMH+rjnedbf1xhtvmPHjxxuPx2OioqLMxRdfbJYtW9aurqva/s1vfmPOP/9843K5zKWXXmreeustv/1//vOfTWpqqmltbT1mv48l2N8zgc7Bjh07Ovxcvvrqq6ek7e6Yg1OFYNuDDB8+3Nx5553O+6+//tqkp6ebq666yvztb38zq1evNsnJyeaOO+445nkeffRRM2vWLDNr1qyjBtsxY8aY9PR0s379erN+/XqTnp5ucnNzA27717/+tbn88stP6rq7S9vxNcaYadOmmYULF5r8/PwO/7Hx+XwmKSnJ3HTTTWbr1q1mxYoVJiYmxsybN8+p+fjjj01UVJS58847zbZt28zixYtNeHi4eeGFF47alyVLlphp06aZN9980/zzn/80zz77rImMjDSPP/74KWn7+uuvN9OnTw9wxE6NtvPQ3WPRliTz9NNPm7q6Ouf1r3/965S0HYx56Oj/9915zW1112du/fr1JjQ01JSWlprt27eb0tJSExYWZjZs2ODX3qWXXmqeeOKJExnKExbM75oTve5veuihh8y9995r/vrXv5qPPvrIPPbYY+ass84yL730Upe3XVZWZsLDw83ixYvNtm3bzJ133mmio6PNzp07nZqvv/7aJCYmmldeeeWExrsjwfye6cwcHAm2a9as8ftcfnMxqafNwalCsO1B2n4QX3nlFXPWWWeZzz77zNn2/PPPG5fLdUIrDG+88UaHwXbbtm1Gkt//0SsrK40k8/777wfU9ieffGIkmX/+85+BXm636+gfmyPuu+++Dv+xeeKJJ4zb7TZfffWVs23WrFkmOTnZ+a/46dOnmwsvvNDvuClTppghQ4YE1L+pU6eaq6666pS0vXTpUpOSkhJQf06VY83DEadyLNqSZFauXHnU/T19Ho4WbLvrmo/mVH/mbrjhBjNmzBi/mpycHHPTTTf5bZs5c6a54oorTqjPJyqY3zUnet3Hc+2115qf/OQnzvuuavvyyy83t912m1/NhRdeaO6++26/bRMnTjT5+fkB9fmbgvk905k5OBJst2zZctSanjYHpwr32PZglZWVSk9PV3JysrMtJydHTU1NqqqqOqnzut1uZWZmOtuGDBkit9ut9evXB9R23759lZiYqLfffrvT/TmdVVZWavjw4X4P0M7JydHnn3+uTz75xKnJzs72Oy4nJ0fvvPOOWlpaTrgtn8+n+Pj4U9L25ZdfrtraWu3cufOE+xNMp3IsOnLHHXcoISFBl112mX7729/63Tdu6zx01zUHqqvaPlrNke+4Iy6//HJt2rRJTU1Nne5zV+ju6z6ejj6DJ9t2c3Ozqqqq2tVkZ2d3OC+n+t+VU/U9czJzMH78eCUmJmrYsGF64YUX/PbZOAedQbDtwerr65WUlOS3LS4uThEREaqvrz+p8yYmJrbbnpiY6Jw3kLa/9a1vOR9623Q0DkfeH2uskpKS9PXXX+uLL744oXYqKyv1hz/8QVOmTDklbX/rW9+SpB4xT6d6LNp68MEH9cc//lFr1qzRTTfdpOLiYpWWlp6Stk+XeejOaw5UV7V9tJqOvr+amppO6ju1K3T3dR/LCy+8oM2bN+snP/nJcfsXSNtffPGFWltbT3hedu3adcr+OPlUfs90Zg569+6t+fPn64UXXtArr7yikSNH6sYbb9SyZcuO27+eOged1aN/UhdSSEhIu23GmA63d/V5T7TtyMhI/etf/zqp/pzO2l6v+f8/5nesseqo5mjee+89XXfddfrlL3+p0aNHn5K2IyMjJem0n6fuGIu27r33Xud/X3LJJZKkBx54wG+7bfPQndfcGV3Vdkc1HX1/ScGfE6l7r/to3nzzTU2cOFGLFy/W9773vS7pX9ttJzovhw8fVlNTkzNHXaU7vmcCnYOEhAT9/Oc/d94PHjxYXq9Xc+bM0S233NLlbQd7Dk4GK7Y9mMfjafdfUF6vVy0tLe3+ayvQ8+7evbvd9r179zrnDaTtffv26Zxzzul0f05nHY3Dnj17JOmYY7Vnzx6FhYWpT58+xzz/tm3bdPXVV6ugoMAvVHR12/v27ZOk03qeumssjmfIkCFqaGhwPiNnwjycymsOVFe1fbSajr6/pODPSXdfd0fWrl2rcePGaf78+frxj398Qv0LpO2EhASFhoae8LxERUV1eaDqju+Zk5mDbxoyZIg+/PDD4/avp83BySLY9mBZWVmqqalRXV2ds62iokIul0sZGRkndV6fz6dNmzY52zZu3Cifz6ehQ4cG1PZXX32lf/7znxo0aFCn+3M6y8rK0ltvvaXm5mZnW0VFhZKTk3X++ec7NatXr/Y7rqKiQoMHD1Z4ePhRz/3ee+/pqquu0oQJE/TQQw+d0rZramoUHh7ebgXmdNGdY3E8W7ZsUa9evXT22Wd3edun6zycymsOVFe1fbSaI99xR9TU1Oi8885TQkJCp/vcFbr7utt68803NXbsWM2ePVuTJ0/usH8n23ZERIQyMjLa1axevbrDebn00kuP2edAddf3TGfnoK0tW7bo3HPP9etfT5+DLtE9f6OGrnC0x32NHDnS/O1vfzNr1qwx55133nEf91VXV2e2bNliFi9ebCSZt956y2zZssV8+eWXTs2YMWPMRRddZCorK01lZaUZOHBgh4/7Ol7bb7zxhundu7c5dOhQ1wzCKdTRX8l++OGHZsuWLWbKlCnmggsuMFu2bDFbtmxxHrGyf/9+k5SUZH70ox+ZrVu3mhdffNHExsZ2+PiXn//852bbtm1myZIlx33sUU1NjTnnnHPMzTff7Pdolz179jg1Xdn2fffdZ66++uqTGb4u03Yeunssvumll14yTz31lNm6dav56KOPzOLFi01sbKwpLCw8JW0HYx7ajnd3X3Nb3fWZ++tf/2pCQ0PN7Nmzzfbt283s2bM7fOTShAkTzK233tqpsT2aYH7XnOh1f9Mbb7xhoqKizIwZM/w+g9/8N6Or2j7yqKklS5aYbdu2maKiIhMdHW0++eSTdmP4wAMPBDbwbY4P1vdMZ+Zg6dKlZvny5Wbbtm3m/fffN3PnzjXh4eFm/vz5Xd52d83BqUKw7UE6+jLcuXOnGTt2rImMjDTx8fHmjjvu8HsUiTH/90zKI+67774OH/T8zZovv/zS3HzzzSYmJsbExMSYm2++ucMfaDhe25MnTzZTpkzpiss/5Toa3+HDh3c4Vjt27HBq/v73v5srrrjCuFwu4/F4zMyZMzt8YPegQYNMRESEOf/889s9NPvIo9eOnPdoc9S3b1+/47qibWOMueCCC8zzzz8f2ICdIm3noTvHou08vPrqq+aSSy4xvXv3NlFRUSY9Pd0sWLDAeah+V7ZtTHDmoe14d+c1tx3vI/3pjs+cMcb88Y9/NGlpaSY8PNxceOGFZsWKFX77GxsbTWxsrKmsrDyRoTxhwfyuMeb41/3000+bb657TZgwocO+DR8+vMvbNubfPw7Qt29fExERYS699FKzdu1av/2ffvqpCQ8PN7W1te2OPVHB/J45kXFoOwdLly41/fv3N1FRUSYmJsZkZGR0+ONHPWkOThWCbQ9yIs/da2vHjh0mLCzM/OMf/zg1nTqGPXv2mPj4+NPmF62OpzPj21Wefvpp893vftc0Nzd3e9svv/yy6d+/f7vgEizMQ/fOw5k63idi4cKFZvTo0V1+3mCO+Ym477772oXW00lJSYkpKCg4qXMwByenK+bgVOEe2x7miSeeUO/evbV169YTqi8vL9fkyZOVmpp6invW3o4dO/TEE0+oX79+3d52ZwU6vl2lvLxcpaWlJ3XvYWcdOnRITz/9tMLCTp+HpDAP3etMHO8TER4erscff/yUnDtYY34iXnvtNc2ZMyfY3TiqxMREPfjggyd9Huag87pqDk6FEGP+/7MgcNr77LPP1NjYKEn69re/rYiIiCD3yC6M7+mBeehejHf3Y8yDjzmwF8EWAAAAVuBWBAAAAFiBYAsAAAArEGwBAABgBYItAAAArECwBQAAgBUItgAAALACwRYAAABWINgCAADACgRbAAAAWOH/ATwiZ0d04HIpAAAAAElFTkSuQmCC )

### 3、sklearn 中的 iris 数据集

#### 3.1 用 sklearn.datasets 导入 iris 数据集，并输出训练数据（前 5 个）、标签/target、特征名/feature_names、类名/target_names。

In [11]:

```
from sklearn.datasets import load_iris
irisdata = load_iris()
print(irisdata.data[:5])
print(irisdata.target)
print(irisdata.feature_names)
print(irisdata.target_names)
[[5.1 3.5 1.4 0.2]
 [4.9 3.  1.4 0.2]
 [4.7 3.2 1.3 0.2]
 [4.6 3.1 1.5 0.2]
 [5.  3.6 1.4 0.2]]
[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2
 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
 2 2]
['sepal length (cm)', 'sepal width (cm)', 'petal length (cm)', 'petal width (cm)']
['setosa' 'versicolor' 'virginica']
```

#### 3.2 将 iris 数据集的训练数据、标签分别转成 pandas.DataFrame 类型，记为dfx、dfy，其中 dfy 的列名记为‘target’，并分别输出。

In [23]:

```
import pandas as pd
dfx = pd.DataFrame(irisdata.data, columns = irisdata.feature_names)
dfy = pd.DataFrame(irisdata.target, columns = ['target'])
print(dfx)
print(dfy)
     sepal length (cm)  sepal width (cm)  petal length (cm)  petal width (cm)
0                  5.1               3.5                1.4               0.2
1                  4.9               3.0                1.4               0.2
2                  4.7               3.2                1.3               0.2
3                  4.6               3.1                1.5               0.2
4                  5.0               3.6                1.4               0.2
..                 ...               ...                ...               ...
145                6.7               3.0                5.2               2.3
146                6.3               2.5                5.0               1.9
147                6.5               3.0                5.2               2.0
148                6.2               3.4                5.4               2.3
149                5.9               3.0                5.1               1.8

[150 rows x 4 columns]
     target
0         0
1         0
2         0
3         0
4         0
..      ...
145       2
146       2
147       2
148       2
149       2

[150 rows x 1 columns]
```

#### 3.3 将 dfx、dfy 拼起来，dfy 在最右边，记为 df，并输出（提示：可以用.concat()方法来拼接）。

In [24]:

```
df = pd.concat([dfx, dfy], axis = 1)
df.head()
```

Out[24]:

|      | sepal length (cm) | sepal width (cm) | petal length (cm) | petal width (cm) | target |
| ---: | ----------------: | ---------------: | ----------------: | ---------------: | -----: |
|    0 |               5.1 |              3.5 |               1.4 |              0.2 |      0 |
|    1 |               4.9 |              3.0 |               1.4 |              0.2 |      0 |
|    2 |               4.7 |              3.2 |               1.3 |              0.2 |      0 |
|    3 |               4.6 |              3.1 |               1.5 |              0.2 |      0 |
|    4 |               5.0 |              3.6 |               1.4 |              0.2 |      0 |

#### 3.4 输出 df 第 1、3、5 行。

In [27]:

```
print(df[1:2])
print(df[3:4])
print(df[5:6])
   sepal length (cm)  sepal width (cm)  petal length (cm)  petal width (cm)  \
1                4.9               3.0                1.4               0.2   

   target  
1       0  
   sepal length (cm)  sepal width (cm)  petal length (cm)  petal width (cm)  \
3                4.6               3.1                1.5               0.2   

   target  
3       0  
   sepal length (cm)  sepal width (cm)  petal length (cm)  petal width (cm)  \
5                5.4               3.9                1.7               0.4   

   target  
5       0  
```

#### 3.5 输出 df 最后三列。

In [36]:

```
print(df[["petal length (cm)", "petal width (cm)", "target"]])
     petal length (cm)  petal width (cm)  target
0                  1.4               0.2       0
1                  1.4               0.2       0
2                  1.3               0.2       0
3                  1.5               0.2       0
4                  1.4               0.2       0
..                 ...               ...     ...
145                5.2               2.3       2
146                5.0               1.9       2
147                5.2               2.0       2
148                5.4               2.3       2
149                5.1               1.8       2

[150 rows x 3 columns]
```

#### 3.6 输出 df 第 1 到第 5 行的第 1、3、target 列。

In [42]:

```
print(df.iloc[1:6,[1, 3, 4]])
   sepal width (cm)  petal width (cm)  target
1               3.0               0.2       0
2               3.2               0.2       0
3               3.1               0.2       0
4               3.6               0.2       0
5               3.9               0.4       0
```

#### 3.7 输出 df 第 3 行第 3 列的元素。

In [43]:

```
print(df.iloc[3, 3])
0.2
```

#### 3.8 将 df 保存成 csv 文件，文件名为‘iris_new.csv’。

In [44]:

```
df.to_csv('d:/iris_new.csv')
```

#### 3.9 绘制散点图 figure 2a，其中第 0、1 列分别为 x、y 坐标，target 等于0、1、2 的分别为红、绿、蓝色。

In [53]:

```
import matplotlib.pyplot as plt
x = irisdata.data
y = irisdata.target
colors = ['red', 'green', 'blue']
for color, i, target_name in zip(colors,[0, 1, 2], irisdata.target_names):
    plt.scatter(x[y == i, 0], x[y == i, 1], color = color, label = target_name)
plt.title('figure 2a')
plt.legend()
```

Out[53]:

```
<matplotlib.legend.Legend at 0x177a0ccd580>
```

![img](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAiQAAAGxCAYAAABSsK0dAAAAOXRFWHRTb2Z0d2FyZQBNYXRwbG90bGliIHZlcnNpb24zLjUuMiwgaHR0cHM6Ly9tYXRwbG90bGliLm9yZy8qNh9FAAAACXBIWXMAAA9hAAAPYQGoP6dpAABQrklEQVR4nO3de1xU1d4/8M84yE0B01QGBkPJ+yXMy0+PUhmZlzI7ZFc9R7N88iETQ8FLZWoZpWXgKTI9HcujZR2HTpplWolZ6lOalkfIPIaChFknAw0DGdbvj4k5DszA7M2efZn5vF+vedXsWXvWWnsxe77OXnt9TUIIASIiIiINtdC6AUREREQMSIiIiEhzDEiIiIhIcwxIiIiISHMMSIiIiEhzDEiIiIhIcwxIiIiISHMMSIiIiEhzDEiIiIhIcwxIiALUm2++id69eyMsLAwmkwmHDh3CokWLYDKZtG6aLHa7HStWrMDo0aNhtVoRHh6Onj17Yt68efjll1+0bh4RNcHEpeOJAs+PP/6I2NhYjB49GrNnz0ZISAj69euHn3/+GadOncKQIUO0bqJk58+fR0xMDO6++26MHDkSl19+Ob788ks8+eSTsFgs2L9/P8LCwrRuJhF5EKR1A4hIfd9++y0uXryISZMm4dprr3VuDw8Ph9Vq1aRNFy5caFbAEBYWhqKiIrRr18657brrrkOnTp1w++23w2azYdKkSUo0lYh8gJdsiALMlClTMHz4cADAnXfeCZPJhOuuuw4A3F6yqaqqwuzZsxEdHY3w8HBcc801OHDgAOLj4zFlyhRnOU+Xe1599VWYTCacOHHCuS0+Ph4333wz8vLy0L9/f4SGhmLx4sUAgNOnT+OBBx6A1WpFcHAwOnfujMWLF6OmpqbRfpnNZpdgpM7gwYMBACUlJc5tv/32G2bPno3ExERERUWhbdu2GDp0KN55551G6yAi3+EvJEQB5rHHHsPgwYPx4IMP4qmnnsKIESMQGRnpsfy9996LN998E5mZmbj++utRUFCAP/7xj6ioqGhWO7788ksUFhbi0UcfRefOndGqVSucPn0agwcPRosWLbBw4UIkJCRg7969ePLJJ3HixAmsXbtWcj0ff/wxAKB3797ObVVVVfj5558xZ84cxMbGorq6Gh9++CFSUlKwdu1a/PnPf25W34hIOgYkRAEmISEBvXr1AgB07dq10fkiBQUFeOONNzB37lxkZWUBAEaOHImOHTvi7rvvblY7zpw5g4KCAnTr1s25bfr06Th79iyOHDmCTp06AQCSk5MRFhaGOXPmICMjw9l2b5SWlmLevHkYOHAgbr75Zuf2qKgol+DGbrcjOTkZZ8+eRXZ2NgMSIg3wkg0RebRr1y4AwB133OGyfcKECQgKat6/Z/r16+cSjADAu+++ixEjRiAmJgY1NTXOx5gxY1za442ff/4ZY8eOhRACb775Jlq0cD3d/eMf/8CwYcPQunVrBAUFoWXLlnjllVdQWFjYrH4RkTwMSIjIo//85z8AgI4dO7psDwoKcjtfQwqLxdJg2w8//IAtW7agZcuWLo+6yy0//fSTV+999uxZjBw5EqWlpdixYwe6dOni8npeXh7uuOMOxMbGYv369di7dy+++OILTJ06Fb/99luz+kVE8vCSDRF5VBd0/PDDD4iNjXVur6mpcQYrdUJDQwE45meEhIQ4t3sKItxNgL388svRr18/LF261O0+MTExTbb57NmzuOGGG1BUVISPPvoI/fr1a1Bm/fr16Ny5M958802XdlRVVTX5/kTkGwxIiMija665BoBjEbWrr77auX3Tpk0N7nqJj48HAHz99dcYNGiQc/uWLVu8ru/mm2/Ge++9h4SEBFx22WWS21sXjHz33XfYsWMH+vfv77acyWRCcHCwSzBy+vRp3mVDpCEGJETkUe/evXH33Xfjueeeg9lsxvXXX48jR47gueeeQ1RUlMu8jLFjx6Jt27a47777sGTJEgQFBeHVV191ud22KUuWLMGOHTvwhz/8ATNnzkT37t3x22+/4cSJE3jvvfewatUqj+ukXLhwAaNGjcLBgweRnZ2Nmpoa7Nu3z/l6+/btkZCQAADOW45TU1MxYcIElJSU4IknnoDFYsGxY8dkHi0iag4GJETUqLVr18JiseCVV17B888/j8TERLz11lsYPXo02rRp4ywXGRmJbdu2YdasWZg0aRLatGmD+++/H2PGjMH999/vVV11K6o+8cQTWL58OU6dOoWIiAh07twZo0ePbvRXkx9++AFffPEFACAtLa3B65MnT8arr74KwHEr85kzZ7Bq1Sr87W9/Q5cuXTBv3jycOnXKuR4KEamLS8cTkWR79uzBsGHDsGHDBtxzzz1aN4eI/AADEiJq1I4dO7B3714MGDAA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 )

## 实验总结与讨论

通过本实验”基于Python的数据分析“我学会了 NumPy 的 ndarray 对象 的向量和矩阵操作，pandas 的输入导入和基于 DateFrame 对象， sklearn 中数据和算法调用，以及基于 matplotlib 的画图。
