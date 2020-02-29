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

void reset_printed_points_matrix(int printed_points[100][100]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printed_points[i][j] = 0;
        }
    }
}

void main_loop() {
    char string[100];
    double coordinates[100], slope, previous_slope;
    double previous_coordinate_x, previous_coordinate_y;
    int number_of_coordinates, sequence_length, maximum_sequence_length;
    int sequence_beginning, maximum_sequence_beginning, maximum_sequence_end;
    int printed_points[100][100];

    while (1) {
        fgets(string, 100, stdin);
        reset_printed_points_matrix(printed_points);
        number_of_coordinates = 0;
        sequence_length = 0;
        maximum_sequence_length = 0;
        sequence_beginning = 0;
        maximum_sequence_beginning = 0;

        if (!strncmp(string, "exit", 4))
            break;

        parse_coordinate_string(string, coordinates, &number_of_coordinates);

        if (number_of_coordinates == 2 || number_of_coordinates == 4) {
            for (int i = 0; i < number_of_coordinates; i++) {
                printf("%d ", (int)coordinates[i]);
            }
            printf("\n");
            continue;
        }

        previous_slope = (coordinates[3]-coordinates[1])/(coordinates[2]-coordinates[0]);
        previous_coordinate_x = coordinates[2];
        previous_coordinate_y = coordinates[3];
        sequence_length = 2;
        int new_sequence_began = 0;

        for (int i = 4; i < number_of_coordinates; i += 2) {
            slope = (previous_coordinate_y - coordinates[i + 1])/(previous_coordinate_x - coordinates[i]);

            if (slope != previous_slope && !new_sequence_began) {
                if (sequence_length > maximum_sequence_length) {
                    maximum_sequence_length = sequence_length;
                    maximum_sequence_beginning = sequence_beginning;
                    maximum_sequence_end = maximum_sequence_beginning + maximum_sequence_length * 2;
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
            maximum_sequence_end = maximum_sequence_beginning + maximum_sequence_length * 2;
        }

        //printf("maximum sequence length: %d\n", maximum_sequence_length);
        //printf("maximum_sequence_beginning: %d\n", maximum_sequence_beginning);
        //printf("maximum sequence end: %d\n", maximum_sequence_end);

        //print longest sequence of collinear points
        for (int i = maximum_sequence_beginning; i < maximum_sequence_end; i += 2) {
            if (!printed_points[(int)coordinates[i]][(int)coordinates[i+1]]) {
                printf("%d %d ", (int)coordinates[i], (int)coordinates[i+1]);
                printed_points[(int)coordinates[i]][(int)coordinates[i+1]] = 1;
            }
        }
        printf("\n");
    }
}

int main() {
    main_loop();
    return 0;
}
