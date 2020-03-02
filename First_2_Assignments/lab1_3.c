#include <stdio.h>
#include <string.h>

void parse_coordinate_string(char coordinates_string[], double coordinates_result[], int *number_of_coordinates) {
    *number_of_coordinates = 0;

    for (int i = 0; i < strlen(coordinates_string); i++) {
        if ('0' <= coordinates_string[i] && coordinates_string[i] <= '9') {
            int number = 0;
            while ('0' <= coordinates_string[i] && coordinates_string[i] <= '9') {
                number = number * 10 + (coordinates_string[i]-'0');
                i++;
            }
            i--;

            coordinates_result[(*number_of_coordinates)] = number;
            (*number_of_coordinates)++;
        }
    }
}


void get_longest_sequence_of_collinear_points(double coordinates[], int* number_of_coordinates, int* start, int* length) {
    double previous_coordinate_x, previous_coordinate_y, slope, previous_slope;
    int sequence_length = 0, maximum_sequence_length = 0;
    int sequence_beginning = 0, maximum_sequence_beginning = 0;

    previous_slope = (coordinates[3]-coordinates[1])/(coordinates[2]-coordinates[0]);
    previous_coordinate_x = coordinates[2];
    previous_coordinate_y = coordinates[3];

    sequence_length = 2;
    int new_sequence_began = 0;

    for (int i = 4; i < *number_of_coordinates; i += 2) {
        slope = (previous_coordinate_y - coordinates[i + 1])/(previous_coordinate_x - coordinates[i]);

        if (slope != previous_slope && !new_sequence_began) {
            if (sequence_length > maximum_sequence_length) {
                maximum_sequence_length = sequence_length;
                maximum_sequence_beginning = sequence_beginning;
            }
            i -= 2;
            previous_coordinate_x = coordinates[i];
            previous_coordinate_y = coordinates[i + 1];
            new_sequence_began = 1;
            sequence_length = 1;
            sequence_beginning = i;
            continue;
        } else {
            sequence_length++;
            new_sequence_began = 0;
        }

        previous_coordinate_x = coordinates[i];
        previous_coordinate_y = coordinates[i + 1];
        previous_slope = slope;
    }

    if (sequence_length > maximum_sequence_length) {
        maximum_sequence_length = sequence_length;
        maximum_sequence_beginning = sequence_beginning;
    }

    *start = maximum_sequence_beginning;
    *length = maximum_sequence_length * 2;
}


void reset_printed_points_matrix(int printed_points[100][100]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printed_points[i][j] = 0;
        }
    }
}


void clear_screen() {
    for (int i = 0; i < 100; i++) {
        printf("\n");
    }
}


void first_option() {
    int iteration = 0;
    char string[100];
    double coordinates[100];
    int number_of_coordinates;
    int printed_points[100][100];
    clear_screen();

    while (1) {
        fgets(string, 100, stdin);
        reset_printed_points_matrix(printed_points);
        number_of_coordinates = 0;

        if (!iteration) {
            iteration++;
            continue;
        }

        if (!strncmp(string, "exit", 4))
            return;

        parse_coordinate_string(string, coordinates, &number_of_coordinates);

        if (number_of_coordinates == 2 || number_of_coordinates == 4) {
            for (int i = 0; i < number_of_coordinates; i++) {
                printf("%d ", (int)coordinates[i]);
            }

            printf("\n");
            continue;
        }

        int start, length;
        get_longest_sequence_of_collinear_points(coordinates, &number_of_coordinates, &start, &length);

        for (int i = start; i < start + length; i += 2) {
            if (!printed_points[(int)coordinates[i]][(int)coordinates[i+1]]) {
                printed_points[(int)coordinates[i]][(int)coordinates[i+1]] = 1;
                printf("%d %d ", (int)coordinates[i], (int)coordinates[i+1]);
            }
        }

        iteration++;
        printf("\n\n");
    }
}


double pow_double_to_unsigned_int(double x, unsigned int n) {
    double result = 1;

    for (int i = 1; i <= n; i++) {
        result *= (double)x;
    }

    return result;
}


void second_option() {
    double x;
    unsigned int n;

    printf("Enter the real number x: ");
    scanf("%lf", &x);

    printf("Enter the natural number n: ");
    scanf("%d", &n);

    double x_to_the_nth_power = pow_double_to_unsigned_int(x, n);
    printf("The result of %lf ^ %d is %lf\n", x, n, x_to_the_nth_power);
}


void print_menu() {
    printf("\n\n\n");
    printf("1. Read a sequence of points and get the longest subsequence of collinear points.\n");
    printf("2. Determine the value x^n, where x is a real number and n is a natural number,\nby using multiplication and squared operations.\n");
    printf("0. Exit the program.\n\n");
}


void main_loop() {
    void (*options[])() = {first_option, second_option};
    clear_screen();

    while (1) {
        print_menu();

        int option_number;
        printf("Enter an option: ");
        scanf("%d", &option_number);
        clear_screen();
        if (option_number == 0)
            break;

        if (option_number > 2 || option_number < 1) {
            printf("There are only 2 options! Enter 1 or 2!\n");
            continue;
        }

        options[option_number-1]();
    }
}

int main() {
    main_loop();
    return 0;
}
