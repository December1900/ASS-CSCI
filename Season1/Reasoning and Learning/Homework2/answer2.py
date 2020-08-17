import math
import sys
from termcolor import colored

# Student Name:Yao XIAO, Student Number:2019180015|6641751

# set init epsilon
epsilon = 0.0001

# set gamma
gamma = 0.9

# set diff to ensure record between iteractor
diff = 1

# set k 
k = 1

status_root = ['S1', 'S2', 'S3', 'S4', 'S5']

init_dist = {'S1': 1, 'S2': -1, 'S3': 0, 'S4': 1, 'S5': 3}

status_step = [{'A': [(0.2, 'S1'),(0.8, 'S2')],'B': [(1, 'S3')],'C': [(1, 'S1')],'D': [(0.8, 'S1'),(0.2, 'S3')]},
               {'A': [(0.7, 'S1'),(0.3, 'S4')],'B': [(0.1, 'S2'),(0.9, 'S4')],'C': [(0.8, 'S3'),(0.2, 'S4')],'D': [(0.8, 'S1'),(0.2, 'S2')]},
               {'A': [(0.5, 'S2'),(0.5, 'S3')],'B': [(0.5, 'S2'),(0.5, 'S3')],'C': [(1, 'S3'),],'D': [(0.5, 'S1'),(0.5, 'S3')]},
               {'A': [(1, 'S4'),],'B': [(0.3, 'S2'),(0.7, 'S4')],'C': [(1, 'S5'),],'D': [(0.5, 'S4'),(0.5, 'S5')]},
               {'A': [(0.3, 'S3'),(0.7, 'S5'),],'B': [(0.6, 'S4'),(0.4, 'S5')],'C': [(0.9, 'S4'),(0.1, 'S5'),],'D': [(0.8, 'S1'),(0.2, 'S5')]}]


temp = {'S1': init_dist['S1'], 'S2': init_dist['S2'], 'S3': init_dist['S3'], 'S4': init_dist['S4'],
        'S5': init_dist['S5']}

while diff > epsilon:
    if k == 1:
        print(colored('when k equals 1:', 'red'))
        print(colored('J(S1) is ' + str(temp['S1']) + '\n' 
              'J(S2) is '+ str(temp['S2']) + '\n'
              'J(S3) is ' + str(temp['S3']) + '\n' 
              'J(S4) is ' + str(temp['S4']) + '\n' 
              'J(S5) is ' + str(temp['S5']),'yellow'))
    else:
        diff = 0
        results = []
        print(colored('\n' + 'when k equals ' + str(k) + ':', 'red'))
        for index, name in enumerate(status_root):
            print(colored('  when it comes to ' + name + ' turn:', 'blue'))
            step = status_step[index]
            max_result = -10086
            max_name = ''
            for key in step:
                print('if ' + name + ' takes step to: ' +key)
                temp_result = float(0)
                for choice in step[key]:
                    temp_result += float(choice[0] * temp[choice[1]])

                final_result = init_dist[name] + gamma * temp_result
                print('the result is ' + str(final_result))

                if max_result < final_result:
                    max_result = final_result
                    max_name = key
            print('In the end, ' + name + ' will takes step to ' + max_name + ' and J(' + name + ') is ' + str(max_result))
            current_diff = math.fabs(temp[name] - max_result)
            print('and current diff is ' + str(current_diff))
            results.append(max_result)
            if diff < current_diff:
                diff = current_diff
            print('and max diff is ' + str(diff))
        if len(temp) == len(results):
            index = 0
            for key in temp:
                temp[key] = results[index]
                index += 1
        print(colored('J(S1) is ' + str(temp['S1']) + '\n' 
              'J(S2) is '+ str(temp['S2']) + '\n'
              'J(S3) is ' + str(temp['S3']) + '\n' 
              'J(S4) is ' + str(temp['S4']) + '\n' 
              'J(S5) is ' + str(temp['S5']),'yellow'))
    k += 1
