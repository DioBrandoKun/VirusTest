import matplotlib.pylab as plt

def main():
    my_file = open("Virus.txt","r")
    x=list()
    fx=list()
    for i in my_file:
        cord=i.split(" ")
        x.append(int(cord[0]))
        fx.append(int(cord[1]))
    graph = plt.axes()
    graph.grid()
    graph.plot(x,fx);
    graph.scatter(x,fx,label="Ill")
    plt.show()
if __name__ == "__main__":
    main()