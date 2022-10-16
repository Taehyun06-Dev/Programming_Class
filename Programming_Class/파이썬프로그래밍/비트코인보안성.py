import numpy as numpy

def testcode(q, z, c):
    p = 1.0 - q
    lam = z * (q/p)
    adder = 1.0
    for k in range(0, z+1):
        poisson = numpy.exp(-lam)
        for i in range(1, k+1):
            poisson = poisson * lam/i
        adder -= poisson * (1-pow(q/p, z-k))
    if (c == 1):
        if(z < 10):
            print("z=%d         P=%s" % (z, format(adder, '.7f')))
        else:
            print("z=%d        P=%s" %(z,format(adder, '.7f')))
    else:
        if (z < 10):
            print("q=%.2f    z=%d     P=%s" % (q, z, format(adder, '.7f')))
        elif (z < 99):
            print("q=%.2f    z=%d    P=%s" % (q, z, format(adder, '.7f')))
        else:
            print("q=%.2f    z=%d   P=%s" % (q, z, format(adder, '.7f')))

def testcode_main():
    # q = 0.1, 0 <= z <= 10
    print("\nRunning some results, we can see the probability drop off exponentially with z.\n")
    print("q=0.1")
    for i in range(0, 11):
        testcode(0.1, i, 1)
    # q = 0.3, 0 <= z <= 50, z = 5n(n은 정수)
    print("\nq=0.3")
    for i in range(0, 51, 5):
        testcode(0.3, i, 1)
    # Solving for P less than 0.1%...
    print("\nSolving for P less than 0.1%...\nP < 0.001")
    list_z = [5, 8, 11, 15, 24, 41, 89, 340]
    a = -1
    for i in numpy.arange(0.10, 0.46, 0.05):
        i_2 = round(i, 3)
        a += 1
        testcode(i_2, list_z[a], 2)


def main():
    testcode_main()

if __name__ == '__main__':
    main()
