
import matplotlib 
import matplotlib.pyplot as plt
import numpy as np
import json
import math

if __name__ == '__main__':

#init values
# путь до json
    path_to_json = '/home/aquafeet/work_01/output.json'
#куда сохраняем
    interaction = "B-B"
    path_to_save_plot = '/home/aquafeet/work_01/images/enrgy_plot'+ interaction +'.png'
# вид взаимодействия

#н.у. для графика
    max_len = 20
    ones = 0.0005





    with open(path_to_json) as json_file:
        data = json.load(json_file)

    r0 = data["R_0"]

    #print(data)
    params = data[interaction]



    x = np.arange(0,max_len,ones)
    #print(x.shape[0])
    #y = np.zeros(x.shape[0], dtype = float)
    #print("Y")
    #print(x)
    #print(y.shape[0], "y")
    #count = 0
    #for i in x:
    #    y[count] = ((params["A1"]*(i-r0)+params["A0"])*math.exp(-params["p"]*(i/r0-1)))\
    #               -math.sqrt(params["qsi"]*params["qsi"]*math.exp(-2*params["q"]*(i/r0-1)))
    #    count+=1
    y = ((params["A1"]*(x-r0)+params["A0"])*np.exp(-params["p"]*(x/r0-1)))\
                   -np.sqrt(params["qsi"]*params["qsi"]*np.exp(-2*params["q"]*(x/r0-1)))
    fig, ax = plt.subplots()
    ax.set_ylim(-10, 10)
    ax.plot(x, y)
    #ax.plot(x, (params["A1"]*(x-r0)+params["A0"])*np.exp(-params["p"]*(x/r0-1)))
    #ax.plot(x, -np.sqrt(params["qsi"]*params["qsi"]*np.exp(-2*params["q"]*(x/r0-1))))
    ax.set(xlabel = 'x', ylabel = 'Energy', title = "Energy "+interaction)
    ax.grid()
    plt.show()
    fig.savefig(path_to_save_plot)
    #print(formula)
    print(data)
