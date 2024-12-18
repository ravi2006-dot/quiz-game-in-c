#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5

typedef struct Question {
    char question[256];
    char options[4][64];
    int correct_option;
    struct Question* next;  
} Question;


Question* createQuestion(const char* q, const char* opt1, const char* opt2, const char* opt3, const char* opt4, int correct_opt)
{
    Question* newQuestion = (Question*)malloc(sizeof(Question));
    strcpy(newQuestion->question, q);
    strcpy(newQuestion->options[0], opt1);
    strcpy(newQuestion->options[1], opt2);
    strcpy(newQuestion->options[2], opt3);
    strcpy(newQuestion->options[3], opt4);
    newQuestion->correct_option = correct_opt;
    newQuestion->next = NULL;  
    return newQuestion;
}


// Function to display a question and its options
void displayQuestion(Question* q)
{
    printf("%s\n", q->question);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, q->options[i]);
    }
}


// Function to check the user's answer
int checkAnswer(Question* q, int user_answer)
{
    return (user_answer == q->correct_option);
}


// Function to add a question to the end of the linked list
void appendQuestion(Question** head, Question* newQuestion)
{
    if (*head == NULL) {
        *head = newQuestion;
    } else {
        Question* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newQuestion;
    }
}



Question* removeQuestion(Question** head, int index)
{
    if (*head == NULL) return NULL;

    Question* temp = *head;
    if (index == 0) {
        *head = temp->next;
        return temp;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return NULL;

    Question* next = temp->next->next;
    Question* removed = temp->next;
    temp->next = next;

    return removed;
}



int getNumberOfQuestions(Question* head)
{
    int count = 0;
    Question* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


int main()
{
    srand(time(NULL));

   
    Question* questionList = NULL;

    
    appendQuestion(&questionList, createQuestion("Which data structure is used in the implementation of recursion?", 
                                                 "Queue", "Stack", "Array", "Tree", 2));
    appendQuestion(&questionList, createQuestion("What is the time complexity of searching an element in a balanced binary search tree (BST)?", 
                                                 "O(n)", "O(log n)", "O(n log n)", "O(1)", 2));
    appendQuestion(&questionList, createQuestion("Which data structure is best for implementing a priority queue?", 
                                                 "Stack", "Heap", "Linked List", "Array", 2));
    appendQuestion(&questionList, createQuestion("What is the worst-case time complexity of quicksort?", 
                                                 "O(n^2)", "O(n log n)", "O(log n)", "O(n)", 1));
    appendQuestion(&questionList, createQuestion("In which data structure do elements follow the First In First Out (FIFO) principle?", 
                                                 "Stack", "Queue", "Linked List", "Tree", 2));

    int score = 0;
    int num_questions = getNumberOfQuestions(questionList);

    printf("Welcome to the Data Structures Quiz Game!\n");

    for (int i = 0; i < MAX_QUESTIONS && num_questions > 0; i++) {
        
        int random_index = rand() % num_questions;
        Question* current_question = removeQuestion(&questionList, random_index);

        displayQuestion(current_question);

        int user_answer;
        printf("Enter your answer (1-4): ");
        scanf("%d", &user_answer);

        if (user_answer >= 1 && user_answer <= 4) {
            if (checkAnswer(current_question, user_answer)) {
                printf("Correct!\n");
                score++;
            } else {
                printf("Incorrect. The correct answer is %d. %s\n", 
                       current_question->correct_option, 
                       current_question->options[current_question->correct_option - 1]);
            }
        } else {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }

        free(current_question);  
        num_questions--;
    }

    printf("Quiz completed! Your score: %d/%d\n", score, MAX_QUESTIONS);

    return 0;
}
