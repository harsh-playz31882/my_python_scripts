import numpy as np
import sympy as sp


def row_echelon_form(matrix):
    A = sp.Matrix(matrix)
    ref_matrix, _ = A.rref()
    return ref_matrix

def get_simplified_equations(ref_matrix):
    """ Generate simplified equations from the REF matrix """
    equations = []
    num_rows, num_cols = ref_matrix.shape
    variables = [sp.Symbol(f'x{i+1}') for i in range(num_cols-1)]  # Create variables for unknowns

    for row in ref_matrix.tolist():
        equation = sum(row[i] * variables[i] for i in range(len(variables))) - row[-1]
        if any(row[:-1]):  # Avoid trivial equations
            equations.append(sp.simplify(equation))

    return equations

def calculate_matrix_rank():
    try:
        # Taking matrix input
        rows = int(input("Enter the number of rows: "))
        cols = int(input("Enter the number of columns (including augmented column if applicable): "))

        print("Enter the matrix elements row-wise:")
        matrix = []
        for _ in range(rows):
            matrix.append(list(map(float, input().split())))

        # Convert list to NumPy array
        mat = np.array(matrix)

        # Calculate rank
        rank = np.linalg.matrix_rank(mat)

        # Get Row Echelon Form
        ref_matrix = row_echelon_form(mat)

        # Get simplified equations
        simplified_equations = get_simplified_equations(ref_matrix)

        # Print results
        print("\nThe rank of the given matrix is:", rank)

        if simplified_equations:
            print("\nSimplified system of equations:")
            for eq in simplified_equations:
                print(eq, "= 0")

    except ValueError:
        print("Invalid input! Please enter valid numbers.")

# Run the function
calculate_matrix_rank()
