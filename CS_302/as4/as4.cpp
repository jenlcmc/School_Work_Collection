/*
 * Assignment 04
 * Descriptions: write a function that is assigned to each thread that computes part
 * of the product of two matrices, and when all the threads are done,
 * the product of two matrices has been computed
 *
 * Input: input file contain size and elements for 2 matrices
 *
 * Output: computed matrix
 */
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>

using namespace std;

// global vectors to compute
vector<vector<int>> matrix1;
vector<vector<int>> matrix2;
vector<vector<int>> res;

// functions prototypes
void mulMatrix(int, int);
vector<vector<int>> setMatrix(vector<vector<int>> &, ifstream &, int, int);
void printMatrix(vector<vector<int>> &);
void writeToFile(ofstream &out);

int main()
{
    // variables for vector and threads
    int n1 = 0, n2 = 0, m1 = 0, m2 = 0;
    string file;
    string line;
    int maxThreads = 0;
    vector<std::thread> threadVec;

    // read file
    cout << "Enter file name: ";
    cin >> file;
    ifstream inFile;
    inFile.open(file);

    // check file input
    while (!inFile.is_open())
    {
        cout << "Can't open file\n";
        exit(1);
    }

    // read in file and use function to set up matrix
    inFile >> n1 >> m1;
    matrix1 = setMatrix(matrix1, inFile, n1, m1);

    inFile >> n2 >> m2;
    matrix2 = setMatrix(matrix2, inFile, n2, m2);

    // close file -> done reading
    inFile.close();

    // resize the compute matrix
    res.resize(n1, vector<int>(m2));

    // assign max threads
    maxThreads = std::thread::hardware_concurrency();

    auto start = std::chrono::system_clock::now();

    // store threads into a vector of threads in a global vector
    for (auto i = 1; i <= n1; i++)
    {
        for (auto j = 1; j <= m2; j++)
        {
            // spawn a thread
            threadVec.push_back(thread(mulMatrix, i, j));
        }

        // join all of the threads before spawning anymore
        // threads if you have the max amount of threads
        // already running concurrently
        if (threadVec.size() >= maxThreads)
        {
            for (int i = 0; i < threadVec.size(); i++)
            {
                threadVec[i].join();
            }
            // clear out the vector of all of the non living
            // threads so we do not push active threads on
            // top of the non live ones
            threadVec.clear();
        }
    }

    // join the threads if there are any running threads after
    // the main loop ends
    for (int i = 0; i < threadVec.size(); i++)
        threadVec[i].join();

    // print matrix
    printMatrix(res);

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << elapsed.count() << '\n';

    //  write to file
    ofstream out("out.txt");
    writeToFile(out);

    return 0;
}

/**
 * @brief wirte the compute matrix into output file
 * @description: if can open file then do nested loop matrix to write output
 * @param out - outfile
 * @Output : None
 */
void writeToFile(ofstream &out)
{
    if (out.is_open())
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                out << res[i][j] << " ";
            }
            out << endl;
        }
    }

    out.close();
}

/**
 * @brief multiple 2 matrices and put it into compute matrix
 * @Descriptions: using nested loops to loop through r and c of
 * matrix 1 and 2 to compute multiply
 * @param r1 - row of matrix 1
 * @param c2 - colum of matrix 2
 */
void mulMatrix(int r1, int c2)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < matrix1[0].size(); k++)
            {
                res[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

/**
 * @brief Set the Matrix object
 * @param matrix - matrix need to be set
 * @param in - input file
 * @param r - row
 * @param c - col
 * @return vector<vector<int>>
 */
vector<vector<int>> setMatrix(vector<vector<int>> &matrix, ifstream &in, int r, int c)
{
    matrix.resize(r, vector<int>(c)); // init size
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            in >> matrix[i][j];
        }
    }
    return matrix;
}

/**
 * @brief print out the matrix
 * @description: using nested loop to access and print out
 * @param matrix - matrix to print out
 */
void printMatrix(vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
