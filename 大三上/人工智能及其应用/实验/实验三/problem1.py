# """
# 设计高效遗传算法的实验中，求解的问题是在-5<=x1,x2<=5上求一下函数的极小值
# y = 20 + x1^2 + x2^2 - 10*(cos 2PIx1 + cos 2PIx2 )
# """
# import matplotlib.pyplot as plt

# from problem1_GA import problem1_GA

# plt.rcParams["font.family"] = "FangSong"
# SCORE_ZQ = []
# for ZQ in range(1, 100):
#     test = problem1_GA(1, 1, ZQ)
#     test.initpopulation()
#     for i in range(50):
#         test.next_generation()
#         generation, answer, score = test.get_what_we_need()
#         if i == 99:
#             print("x = " + str(answer[0])+", y = "+str(answer[1]))
#         pass

#     x1, x2, x3 = test.draw()
#     SCORE_ZQ.append(score)

# plt.plot(range(99), SCORE_ZQ)
# plt.xlabel("种群数量")
# plt.ylabel("种群平均适应度")
# plt.title("种群数量对于种群平均适应度的影响")
# plt.show()

# """
# 设计高效遗传算法的实验中，求解的问题是在-5<=x1,x2<=5上求一下函数的极小值
# y = 20 + x1^2 + x2^2 - 10*(cos 2PIx1 + cos 2PIx2 )
# """
# import matplotlib.pyplot as plt

# from problem1_GA import problem1_GA

# plt.rcParams["font.family"] = "FangSong"
# SCORE_ZQ = []
# p_list = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
# for p in p_list:
#     test = problem1_GA(1, p, 100)
#     test.initpopulation()
#     for i in range(50):
#         test.next_generation()
#         generation, answer, score = test.get_what_we_need()
#         if i == 99:
#             print("x = " + str(answer[0])+", y = "+str(answer[1]))
#         pass

#     x1, x2, x3 = test.draw()
#     SCORE_ZQ.append(score)


# plt.plot(p_list, SCORE_ZQ)
# plt.xlabel("变异概率")
# plt.ylabel("种群平均适应度")
# plt.title("变异概率对于种群平均适应度的影响")
# plt.show()


"""
设计高效遗传算法的实验中，求解的问题是在-5<=x1,x2<=5上求一下函数的极小值
y = 20 + x1^2 + x2^2 - 10*(cos 2PIx1 + cos 2PIx2 )
"""
import matplotlib.pyplot as plt

from problem1_GA import problem1_GA

plt.rcParams["font.family"] = "FangSong"
SCORE_ZQ = []
p_list = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
for p in p_list:
    test = problem1_GA(p, 1, 100)
    test.initpopulation()
    for i in range(1000):
        test.next_generation()
        generation, answer, score = test.get_what_we_need()
        
        pass

    x1, x2, x3 = test.draw()
    SCORE_ZQ.append(score)


plt.plot(p_list, SCORE_ZQ)
plt.xlabel("交叉概率")
plt.ylabel("种群平均适应度")
plt.title("交叉概率对于种群平均适应度的影响")
plt.show()
