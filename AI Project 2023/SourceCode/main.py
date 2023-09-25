
# Sheila Gallardo Redondo || 100472913
# Alexandra Perruchot-Triboulet Rodríguez || 100453024

from Functions_MDP import solve_MDP # Import the function we have created to solve MDPs in a general way.

if __name__ == '__main__':
    costs = {'on': (0.5 + 0.1675), 'off': (0.5 + 0)} # Define the cost of the actions of your MDP.
    goal = 'grados22' # Define the GOAL.

    # We now call the function that solves MDP's given as input the parameters:
        # the file with the transitions of the MDP.
        # the dictionary associating actions with their costs.
        # the GOAL.
    [policy, value] = solve_MDP('Transitions.txt', costs, goal) 

    #Print the results
    print("Optimal policy with its cost for every Temperature:\n")
    print("Temperature(ᵒC)\tOptimal policy\t\tCost")
    print("16ᵒC\t\t",policy['grados16'],"\t\t",value['grados16'])
    print("16.5ᵒC\t\t",policy['grados16.5'],"\t\t",value['grados16.5'])
    print("17ᵒC\t\t",policy['grados17'],"\t\t",value['grados17'])
    print("17.5ᵒC\t\t",policy['grados17.5'],"\t\t",value['grados17.5'])
    print("18ᵒC\t\t",policy['grados18'],"\t\t",value['grados18'])
    print("18.5ᵒC\t\t",policy['grados18.5'],"\t\t",value['grados18.5'])
    print("19ᵒC\t\t",policy['grados19'],"\t\t",value['grados19'])
    print("19.5ᵒC\t\t",policy['grados19.5'],"\t\t",value['grados19.5'])
    print("20ᵒC\t\t",policy['grados20'],"\t\t",value['grados20']) 
    print("20.5ᵒC\t\t",policy['grados20.5'],"\t\t",value['grados20.5'])
    print("21ᵒC\t\t",policy['grados21'],"\t\t",value['grados21'])
    print("21.5ᵒC\t\t",policy['grados21.5'],"\t\t",value['grados21.5'])
    print("22ᵒC\t\t", policy['grados22'],"\t\t", value['grados22']) 
    print("22.5ᵒC\t\t",policy['grados22.5'],"\t\t",value['grados22.5'])
    print("23ᵒC\t\t",policy['grados23'],"\t\t",value['grados23'])
    print("23.5ᵒC\t\t",policy['grados23.5'],"\t\t",value['grados23.5'])
    print("24ᵒC\t\t",policy['grados24'],"\t\t",value['grados24']) 
    print("24.5ᵒC\t\t",policy['grados24.5'],"\t\t",value['grados24.5'])
    print("25ᵒC\t\t",policy['grados25'],"\t\t",value['grados25'])
