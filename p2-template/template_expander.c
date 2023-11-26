/**
 * Code for template expansion.  Fill in the functions below with 
 * suitable code.
 * 
 * Feel free to declare additional functions as needed.  You should
 * also document your code with comments.
*/

// Global parameters
#include <stdio.h>
#include <string.h>

// Global parameters
#define MAX_STUDENTS 100
#define MAX_STRING_LENGTH 20

// Read in the students from a file. Return the number of students.
int read_csv(char *filename, char names[MAX_STUDENTS][MAX_STRING_LENGTH], char rollnos[MAX_STUDENTS][MAX_STRING_LENGTH], int marks[MAX_STUDENTS]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    int num_students = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d", names[num_students], rollnos[num_students], &marks[num_students]);
        num_students++;
    }

    fclose(file);
    return num_students;
}

// Compute the grade and update the arrays.
void compute_grade(int marks[MAX_STUDENTS], char grades[MAX_STUDENTS][MAX_STRING_LENGTH], int num_students) {
    for (int i = 0; i < num_students; i++) {
        if (marks[i] >= 90) strcpy(grades[i], "S");
        else if (marks[i] >= 80) strcpy(grades[i], "A");
        else if (marks[i] >= 70) strcpy(grades[i], "B");
        else if (marks[i] >= 60) strcpy(grades[i], "C");
        else if (marks[i] >= 50) strcpy(grades[i], "D");
        else if (marks[i] >= 40) strcpy(grades[i], "E");
        else strcpy(grades[i], "U");
    }
}

void write_file(char *tmpfile, char names[MAX_STUDENTS][MAX_STRING_LENGTH], char rollnos[MAX_STUDENTS][MAX_STRING_LENGTH], int marks[MAX_STUDENTS], char grades[MAX_STUDENTS][MAX_STRING_LENGTH], int num_students) {
    FILE *input = fopen(tmpfile, "r");
    if (!input) {
        perror("Error opening template file");
        return;
    }

    for (int i = 0; i < num_students; ++i) {
        FILE *output;
        char output_filename[MAX_STRING_LENGTH + 5]; // +5 for ".txt\0"
        sprintf(output_filename, "%s.txt", rollnos[i]);
        output = fopen(output_filename, "w");

        char line[256];
        while (fgets(line, sizeof(line), input)) {
            char *name_placeholder = strstr(line, "{name}");
            if (name_placeholder) {
                fprintf(output, "%.*s%s%s", (int)(name_placeholder - line), line, names[i], name_placeholder + 6);
            } else {
                char *rollno_placeholder = strstr(line, "{rollno}");
                char *marks_placeholder = strstr(line, "{marks}");
                char *grade_placeholder = strstr(line, "{grade}");

                if (rollno_placeholder) {
                    fprintf(output, "%.*s%s%s", (int)(rollno_placeholder - line), line, rollnos[i], rollno_placeholder + 8);
                } else if (marks_placeholder) {
                    fprintf(output, "%.*s%d%s", (int)(marks_placeholder - line), line, marks[i], marks_placeholder + 7);
                } else if (grade_placeholder) {
                    fprintf(output, "%.*s%s%s", (int)(grade_placeholder - line), line, grades[i], grade_placeholder + 7);
                } else {
                    fprintf(output, "%s", line);
                }
            }
        }
        fseek(input, 0, SEEK_SET); // Reset file pointer to the beginning for the next student
        fclose(output);
    }

    fclose(input);
}
int main() {
    // Declare arrays to hold the data read from CSV
    char names[MAX_STUDENTS][MAX_STRING_LENGTH];
    char rollnos[MAX_STUDENTS][MAX_STRING_LENGTH];
    int marks[MAX_STUDENTS];
    char grades[MAX_STUDENTS][MAX_STRING_LENGTH];

    char filename[] = "students.csv"; // Adjust the filename accordingly
    char tmpfile[] = "template.txt";  // Adjust the filename accordingly
    int num_students;

    num_students = read_csv(filename, names, rollnos, marks);

    compute_grade(marks, grades, num_students);

    // Loop over all students
    for (int i = 0; i < num_students; ++i) {
        write_file(tmpfile, names, rollnos, marks, grades, num_students);
    }

    return 0;
}
