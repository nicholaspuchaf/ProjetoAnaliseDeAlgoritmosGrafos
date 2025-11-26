import gurobipy as gp
from gurobipy import GRB
import sys, time


def format3(x: float) -> str:
    r = round(x * 1000.0) / 1000.0
    s_fixed = f"{r:.3f}"    
    if '.' not in s_fixed:
        return s_fixed 
    s = s_fixed
    while s.endswith('0'):
        s = s[:-1]
    if s.endswith('.'):
        s = s[:-1]
    return s

def solve_shortest_path_gurobi_stdin():     
    first_line = sys.stdin.readline().strip().split()
    N, M, S, D = map(int, first_line)

    vertices = range(N)
    edges = {}
    
    for _ in range(M):
        line = sys.stdin.readline().strip().split()
        u, v, w = line
        u, v = int(u), int(v)
        w = float(w)
        
        edges[(u, v)] = w
        edges[(v, u)] = w 
        
    model = gp.Model("CaminhoMinimo_PL")
    x = model.addVars(edges.keys(), vtype=GRB.BINARY, name="x")
    start_time = time.perf_counter()
    obj_expr = gp.quicksum(edges[u, v] * x[u, v] for u, v in edges.keys())
    model.setObjective(obj_expr, GRB.MINIMIZE)
    model.setParam('OutputFlag', 0)
    adj_out = {i: [] for i in vertices}
    adj_in = {i: [] for i in vertices}
    for u, v in edges.keys():
        adj_out[u].append((u, v))
        adj_in[v].append((u, v))
    for i in vertices:
        outgoing_edges = adj_out[i]
        incoming_edges = adj_in[i]
        flow_out = gp.quicksum(x[u, v] for u, v in outgoing_edges)
        flow_in = gp.quicksum(x[u, v] for u, v in incoming_edges)
        if i == S:
            balance = 1
        elif i == D:
            balance = -1
        else:
            balance = 0
        model.addConstr(flow_out - flow_in == balance, name=f"ConservacaoFluxo_{i}")
    model.optimize()

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    if model.status == GRB.OPTIMAL:
        min_distance = model.objVal
        print(f"{format3(min_distance)}")
        print(f"# Tempo de execução do Gurobi: {elapsed_time:.6f} segundos", file=sys.stderr)
        return min_distance
    elif model.status == GRB.INFEASIBLE:
        print(f"Infeasible: Não foi encontrado um caminho de {S} para {D}.", file=sys.stderr)
        return None
    else:
        print(f"Otimização finalizada com status: {model.status}", file=sys.stderr)
        return None


if __name__ == "__main__":
    solve_shortest_path_gurobi_stdin()