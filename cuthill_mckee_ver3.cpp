#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std;

typedef vector <pair<int, double>> vec_int_double;

double Random(double min, double max) {
    return (double)(rand()) / (double)(RAND_MAX / (max - min)) + min;
}

vector <pair<int, int>> NonRepeating(int n) {
    vector <pair<int, int>> unique;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i >= j) {
                unique.push_back({ i,j });
            }
    random_shuffle(unique.begin(), unique.end());
    return unique;
}

vector <vec_int_double> SetGraph(int nonzero, int range, int n) {

    vector <vec_int_double> adj(n);
    int count = 0, u, v;
    vector <pair<int, int>> unique = NonRepeating(n);

    cout << "ok" << endl;

    for (int i = 0; i < nonzero; i++) {

        u = unique[count].first;
        v = unique[count].second;
        count++;


        double w = Random(-range, range);

        if (u == v) {
            adj[u].push_back({ v, w });
        }
        else {
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w });
            i++;
        }
    }

    return adj;
}

void PrintGraph(vector <vec_int_double> adj, ofstream & fout) {
    for (int i = 0; i < adj.size(); i++) {
        fout << i << ": " << endl;
        for (int j = 0; j < adj[i].size(); j++) {
            fout << "    -> " << adj[i][j].first << " (" << adj[i][j].second << ")" << endl;
        }
    }
    fout << endl;
}

void PrintSystem(vector <vec_int_double> adj, int n, bool exp, double* variables, double* solutions, ofstream & fout) {
    if (exp == true) {

        if (150 - n * 10 > 30) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(10) << scientific << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(10) << scientific << 0;
                    }
                }
                if (i == (int)(n / 2)) {
                    cout << "    *" << setw(10) << scientific << variables[i] << "    =" << setw(10) << scientific << solutions[i] << endl;
                }
                else {
                    cout << setw(5) << " " << setw(10) << scientific << variables[i] << setw(5) << " " << setw(10) << scientific << solutions[i] << endl;
                }
            }
        }
        else {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(10) << scientific << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(10) << scientific << 0;
                    }
                }
                cout << setw(60) << " ";

                cout << setw(10) << scientific << variables[i] << setw(5) << " " << setw(9) << scientific << solutions[i] << endl;

            }
            cout << setw(52) << " " << " . " << setw(62) << "." << setw(15) << "." << endl;
            cout << setw(55) << " " << " . " << setw(55) << "  *  " << "   .    =  " << setw(8) << "." << endl;
            cout << setw(58) << " " << " . " << setw(56) << "." << setw(15) << "." << endl;

            for (int i = n - 5; i < n; i++) {
                cout << setw(56) << " ";
                for (int j = n - 5; j < n; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(10) << scientific << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(10) << scientific << 0;
                    }
                }
                cout << setw(4) << " ";
                cout << setw(10) << scientific << variables[i] << setw(5) << " " << setw(9) << scientific << solutions[i] << endl;
            }
        }

        fout.precision(1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bool found = false;
                for (int k = 0; k < adj[i].size(); k++)
                    if (j == adj[i][k].first) {
                        fout << setw(10) << scientific << adj[i][k].second;
                        found = true;
                        break;
                    }
                if (found == false) {
                    fout << setw(10) << scientific << 0 ;
                }
            }
            fout << setw(10) << " " << endl;

        }
        fout << '\n' << '\n' << '\n';
    }
    else {
        if (150 - n * 10 > 30) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(8) << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(8) << 0;
                    }
                }
                if (i == (int)(n / 2)) {
                    cout << "    *" << setw(8) << variables[i] << "    =" << setw(8) << solutions[i] << endl;
                }
                else {
                    cout << setw(5) << " " << setw(8) << variables[i] << setw(5) << " " << setw(8) << solutions[i] << endl;
                }
            }
        }
        else {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(8) << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(8) << 0;
                    }
                }
                cout << setw(58) << " ";

                cout << setw(8) << variables[i] << setw(5) << " " << setw(10) << solutions[i] << endl;

            }
            cout << setw(49) << " " << " . " << setw(60) << "." << setw(13) << "." << endl;
            cout << setw(51) << " " << " . " << setw(54) << "  *  " << "   .    =  " << setw(6) << "." << endl;
            cout << setw(53) << " " << " . " << setw(56) << "." << setw(13) << "." << endl;

            for (int i = n - 6; i < n; i++) {
                cout << setw(54) << " ";
                for (int j = n - 6; j < n; j++) {
                    bool found = false;
                    for (int k = 0; k < adj[i].size(); k++)
                        if (j == adj[i][k].first) {
                            cout << setw(8) << adj[i][k].second;
                            found = true;
                            break;
                        }
                    if (found == false) {
                        cout << setw(8) << 0;
                    }
                }
                cout << setw(4) << " ";
                cout << setw(8) << variables[i] << setw(5) << " " << setw(10) << solutions[i] << endl;
            }
        }
        fout.precision(2);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bool found = false;
                for (int k = 0; k < adj[i].size(); k++)
                    if (j == adj[i][k].first) {
                        fout << setw(8) << adj[i][k].second;
                        found = true;
                        break;
                    }
                if (found == false) {
                    fout << setw(8) << 0;
                }
            }
            if (i == (int)(n / 2)) {
                fout << "    *" << setw(8) << variables[i] << "    =" << setw(8) << solutions[i] << endl;
            }
            else {
                fout << setw(5) << " " << setw(8) << variables[i] << setw(5) << " " << setw(8) << solutions[i] << endl;
            }
        }

        fout << '\n' << '\n' << '\n';
        
    }
}

void Multiplication(vector <vec_int_double> adj, double* variables, double* solutions, int n) {
    for (int i = 0; i < n; i++) {
        solutions[i] = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < adj[i].size(); k++)
                if (j == adj[i][k].first) {
                    solutions[i] += variables[j] * adj[i][k].second;
                    break;
                }
        }
    }
}

int minDegree(vector <vec_int_double> adj, int range, vector <int> permutations) {
    int minSize = adj.size();
    int node;
    for (int i = 0; i < adj.size(); i++) {
        int degree = minSize;
        bool picked = false;
        bool unique = true;
        if (adj[i].size() != 0) {
            for (int k = 0; k < permutations.size(); k++)
                if (i == permutations[k])
                    unique = false;
            if (unique == true) {
                degree = adj[i].size();
                for (int j = 0; j < adj[i].size(); j++) {
                    if (i == adj[i][j].first) {
                        degree--;
                    }
                }
                if (degree == 0) {
                    degree = adj.size();
                }
                if (minSize > degree) {
                    node = i;
                    minSize = degree;
                }
            }
        }
    }
    return node;
}

double NodeDegree(vector <vec_int_double> adj, int node) {
    int degree = adj[node].size();
    for (int i = 0; i < adj[node].size(); i++)
        if (node == adj[node][i].first) {
            degree--;
        }
    if (degree == 0)
        degree = adj.size();
    return degree;
}

vector <int> SortQueue(vector <vec_int_double> adj, vector <int> queue) {
    int tmp;
    vector <int> srtQueue = queue;

    for (int i = 0; i < srtQueue.size() - 1; i++) {
        if (NodeDegree(adj, queue[i]) > NodeDegree(adj, queue[i + 1])) {
            tmp = srtQueue[i + 1];
            srtQueue[i + 1] = srtQueue[i];
            srtQueue[i] = tmp;
        }
    }

    return srtQueue;
}

vector <int> SetQueueOfNode(vector <vec_int_double> adj, vector <int> queue, vector <int> permutations, int range) {
    vector <int> unique = permutations;
    for (int i = 0; i < queue.size(); i++)
        unique.push_back(queue[i]);

    vector <int> updQueue;
    int& node = permutations.back();
    for (int i = 0; i < adj[node].size(); i++) {
        bool unique = true;
        for (int k = 0; k < permutations.size(); k++) {
            if (adj[node][i].first == permutations[k])
                unique = false;
        }
        if (node != adj[node][i].first && unique == true) {
            updQueue.push_back(adj[node][i].first);
        }
    }

    if (updQueue.size() == 0) {
        updQueue.push_back(minDegree(adj, range, unique));
    }

    updQueue = SortQueue(adj, updQueue);
    return updQueue;
}

auto SizeOfPermutations(vector <vec_int_double> adj) {
    int size = adj.size();
    vector<int> indeсes;
    bool set = false;
    for (int i = 0; i < adj.size(); i++) {
        if ((adj[i].size() == 1 && adj[i][0].first == i) || (adj[i].size() == 0))
            size--;
        else
            indeсes.push_back(i);
    }
    return make_pair(size, indeсes);
}

vector<int> BandwidthReduction(vector <vec_int_double> adj, int range) {
    vector <vec_int_double> newAdj(adj.size());
    vector <int> permutations;
    vector <int> queue;

    permutations.push_back(minDegree(adj, range, permutations));

    while (permutations.size() < SizeOfPermutations(adj).first) {

        queue = SetQueueOfNode(adj, queue, permutations, range);

        for (int i = 0; i < queue.size(); i++) {
            permutations.push_back(queue[i]);
        }
    }
    return permutations;
}

bool SetOutputFormat(int range) {
    bool isExponential = false;
    cout << endl << fixed;
    if (range <= 100)
        cout.precision(2);
    else {
        isExponential = true;
        cout.precision(1);
    }
    return isExponential;
}

vector <vec_int_double> SetPermutations(vector <vec_int_double> adj, vector <int> indeces, vector <int> permutations) {
    vector <vec_int_double> newAdj = adj;

    for (int i = 0; i < indeces.size(); i++)
        newAdj[indeces[i]] = adj[permutations[i]];

    for (int i = 0; i < newAdj.size(); i++) 
        for (int j = 0; j < newAdj[i].size(); j++)
            for (int k = 0; k < permutations.size(); k++) {
                if (newAdj[i][j].first == permutations[k]) {
                    newAdj[i][j].first = indeces[k];
                    break;
                }
            }
    return newAdj;
}

double* PrmtdVariables(double* variables, vector <pair <int, int>>  colsPerm, vector <int> indeces, int n) {
    double* permtdVars = new double[n];
    for (int i = 0; i < n; i++) {
        permtdVars[i] = variables[i];
    }
    for (int i = 0; i < colsPerm.size(); i++) {
        swap(permtdVars[colsPerm[i].first], permtdVars[colsPerm[i].second]);
    }
    return permtdVars;
    delete[] permtdVars;
}

auto NodesPermutations(vector <int> indeces, vector <int> permutations) {
    vector<vector<int>> nodesPermFull;
    vector <pair <int, int>> nodesPermShort;
    vector<int> iter = permutations;
    nodesPermFull.push_back(iter);

    for (int i = 0; i < iter.size() - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < iter.size(); j++)
        {
            if (iter[j] < iter[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(iter[i], iter[min_index]);
            nodesPermFull.push_back(iter);
            nodesPermShort.push_back({ iter[i] , iter[min_index] });
        }
    }
    reverse(nodesPermFull.begin(), nodesPermFull.end());
    return make_pair(nodesPermFull, nodesPermShort);
}

int main() {

    system("mode con cols=150");
    srand(time(NULL));
    
    int n, sparsity, range, i;
    cout << "Enter cols/rows count in an initial symmetric matrix: ";
    cin >> n;
    cout << "Enter sparsity of the symmetric matrix in percents (from 55 to 85): ";
    cin >> sparsity;
    cout << "Enter a range of random values: ";
    cin >> range;
    if (range <= 0 || n <= 1 || sparsity > 85 || sparsity < 55) {
        cout << "Please, enter correct values";
        return 0;
    }

    ofstream foutGraphs("output_graphs.txt");

    ofstream foutSystem("output_systems.txt");

    int nonzero = ((double)(n * n) * (1.0 - (double)sparsity / 100));

    ifstream finGraph("input_matrix_example_1.txt");

    vector <vec_int_double> adj = SetGraph(nonzero, range, n);

    double* variables = new double[n];
    double* prmtdVars = new double[n];
    double* initialSolutions = new double[n];
    double* checkSolutions = new double[n];

    for (i = 0; i < n; i++)
        variables[i] = Random(-range, range);

    PrintGraph(adj, foutGraphs);

    Multiplication(adj, variables, initialSolutions, n);

    PrintSystem(adj, n, SetOutputFormat(range), variables, initialSolutions, foutSystem);

    vector <int> oldNodesToIndeces = BandwidthReduction(adj, range);

    vector <int> indeсes = SizeOfPermutations(adj).second;

    reverse(oldNodesToIndeces.begin(), oldNodesToIndeces.end());

    vector <vector <int>> NodesPerm = NodesPermutations(indeсes, oldNodesToIndeces).first;

    vector <pair <int, int>> NodesPermShort = NodesPermutations(indeсes, oldNodesToIndeces).second;
    
    
    ofstream foutColsRows("nodes_permutations.txt");
    for (int i = 0; i < NodesPerm.size(); i++) {
        foutColsRows << i << ": " << endl;
        for (int j = 0; j < NodesPerm[i].size(); j++) {
            foutColsRows << "    -> " << NodesPerm[i][j] <<  endl;
        }
    }
    foutColsRows << endl;

    for (int i = 0; i < NodesPermShort.size(); i++) {
        foutColsRows << i << ": " << NodesPermShort[i].first << " <-> " << NodesPermShort[i].second << endl;
    }
    foutColsRows << endl;
    foutColsRows.close();
    
    vector <vec_int_double> newAdj = SetPermutations(adj, indeсes, oldNodesToIndeces);
    
    PrintGraph(newAdj, foutGraphs);

    foutGraphs.close();

    prmtdVars = PrmtdVariables(variables, NodesPermShort, indeсes, n);

    Multiplication(newAdj, prmtdVars, checkSolutions, n);
    
    PrintSystem(newAdj, n, SetOutputFormat(range), prmtdVars, checkSolutions, foutSystem);
    
    foutSystem.close();

    cout << endl;
    cout << "graph nodes switches:" << endl;
    cout << "old" << '\t' << "new" << endl;
    for (int i = 0; i < oldNodesToIndeces.size(); i++) {
        cout << oldNodesToIndeces[i] << "   ->   " << indeсes[i] << endl;
    }

    delete[] variables;
    delete[] prmtdVars;
    delete[] initialSolutions;
    delete[] checkSolutions;

    return 0;
}