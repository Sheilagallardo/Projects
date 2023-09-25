
# Sheila Gallardo Redondo || 100472913
# Alexandra Perruchot-Triboulet Rodríguez || 100453024

class Transition(): # class to generate transitions

    def __init__(self, from_state: str, action: str,probability: float,to_state: str):
        self.origin = from_state
        self.action = action
        self.probability = probability
        self.destination = to_state


class MDP(): # Definition of our MDP
    
    def __init__(self, states: set, actions: set): 
        self._states={} # We generate dictionary inside of another dictionary.
        #where the first dictionary's keys will be the states (origin states) and the second's dictionary keys are the actions of our MDP.
        for v in states:
            self._states[v] = {} # each state will have a corresponding dictionary where we are going to store:
            #the actions(keys) and each will have a corresponding list with the destination state and probability.
            for a in actions: # for each action
                self._states[v][a]= []# we initialize each key's list as an empty list.
                # in this list, we will insert the destination state and the corresponding probability (each pair will be a list)

    def add_transition(self,transition: Transition):
    # this function adds a transition to the MDP
        if transition.origin not in self._states: 
        # the origin state is not in the set of states.
            print("Error: state doesn't exist")
            return 
        if transition.destination not in self._states:
         # the destination state is not in the set of states.
            print("Error: state doesn't exist")
            return 
        # Insert a list with the corresponding destination state and probability at the corresponding list of the dictionary (of corresponding action):
        self._states[transition.origin][transition.action].append([transition.destination, transition.probability]) 

    def solve_bellman(self, cost: dict, goal: str): # function to solve the bellman's equations of our MDP
    # cost is a dictionary where we associate each action(keys) with their respectively cost(values).
        bellman={}  # This is a dictionary to store the results (expected values of each state) of bellman's equations and work with them at each iteration.
        for v in self._states.keys():
            bellman[v]= 0.0 # At the first iteration every expected value is 0.

        bellman_aux = {} # An auxiliar dictionary to store the expected values for each state of the current iteration.
        optimal_policy = {} # Dictionary to store the optimal policy for each state.
        
        while(1): # keep computing expected values until we get the precision we want (the fixed point) in all of the expected values.
            cont = False # Variable to check when we have to stop the loop (when we have the precission we want)
            for state in self._states.keys(): # We have to calculate the bellman's equation for each state
                if state == goal: # The expected value of the goal is always 0
                    bellman_aux[state] = 0
                    optimal_policy[state] = None
                else: # If the state is not the goal we have to calculate the bellman equation
                    eq = {} # Dictionary to store the value of the equation for each action (to then choose the minimum between those).
                    for action in cost.keys(): # To calculate the expected value for each state.
                        if len(self._states[state][action]) > 0:
                            sum = cost[action] # Start adding the corresponding cost.
                            for i in self._states[state][action]: # This is to calculate the addition of all transitions from the current state with the corresponding action.
            # we add to the variable sum the previous expected value of the destination state (stored in the bellman's dictionary) times the probability of this transition:
                                sum+=bellman[i[0]]*i[1] 
                            eq[action] = sum # Store the result in the dictionary 'eq'.
                    min_key = min(eq, key=lambda x: eq[x]) # Take the key (the action) of the minimun result stored at eq.
                    bellman_aux[state] = eq[min_key] # Store the new expected value in the auxiliar dictionary
                    optimal_policy[state] = min_key # Store the key of the minimun value in this dictionary (at last iteration it would be the optimal policy for each state)
    
            for state in self._states.keys(): # When the bellman's equation is completed for every state, we store the results in the bellman dictionary to do the next iteration
                if abs(bellman[state]-bellman_aux[state])>0.0001: # to check if the precision is correct (if there's one state's expected value that hasn't reach the fixed point we keep iterating)
                    cont = True # to continue iterating
                bellman[state] = bellman_aux[state] # we store the expected value in the dictionary
            
            if not cont: # If cont = False, it means that every expected value has reached the fixed point (the given precision)
                break # exit the while loop

        return bellman, optimal_policy # we return the expected values and the optimal policy for each state.



# We define this function to read the file, extract the information (states, actions and probabilities) and store it.
def read_file(filename: str):
    file = open(filename, 'r') # we open the Transiciones.txt where we have the transitions for this MDP and we read it.
    read_file = file.read().split('\n') # we split the data from the file; each time we have '\n' it will be an element of the vector read_file.
    states = set() # to store the states of our MDP.
    actions = set() # to store the actions of our MDP.
    list_transitions = [] # store elements of type 'Transition' (transitions of our MDP)
    for line in read_file:
        lines = line.split('--') # we split each line from the file; each time we fin '--', we separate it as an element of the vector 'lines'.
        states.add(lines[0]) # we add all states (first element of the vector 'lines') from the file into the set 'states'.
        actions.add(lines[1]) # we add all actions (second element of the vector 'lines') from the file into the set 'actions'.
        states.add(lines[3]) # in case the state is only a destination state (it may be the case for the goal), we store it too.
        # we create a transition for each line in the file:
        transition = Transition(lines[0], lines[1], float(lines[2]), lines[3]) 
        #we insert the transition into the list of transitions:
        list_transitions.append(transition) 
    return states, actions, list_transitions


# We define this function to create the MDP, it takes as input the set of states and the transition_list.
def create_MDP (states: set, actions: set, transition_list: list):
    mdp = MDP(states, actions) #we create our MDP with the set of states obtained in the read_file function above.
    for transition in transition_list:
        mdp.add_transition(transition) # we insert in the MDP a transition from the transition_list, which we obtained in the read_file function above.
    return mdp

# We define this function to obtain the optimal policy and the expected values taken as inputs the file name, costs and goal:
def solve_MDP(file_name: str, costs: dict, goal: str): 
    [states, actions, transitions] = read_file(file_name) # Call the function read_file to read the file containing the transitions of our MDP
    # we obtain the set of states, set of actions and the list of transitions.
    mdp = create_MDP(states, actions, transitions) # call the function to create the MDP with the output data from the read_file function.
    [expected_values, optimal_policy] = mdp.solve_bellman(costs, goal) # Call the corresponding function to solve the bellman's equation.
    return optimal_policy, expected_values # returns the optimal_policy
    