#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Common declarations
#define MAX_TEXTFILE_SIZE       4096
#define MAX_FILENAME_LENGTH       80
#define MAX_NUMBER_AGENTS         15
#define MAX_AGENTNAME_LENGTH      45
#define MAX_LINE_LENGTH           96

typedef struct {
    char name[MAX_AGENTNAME_LENGTH];
    size_t key;
} Agent;

typedef struct {
    size_t size;
    size_t next;
    Agent  pool[MAX_NUMBER_AGENTS];
} AgentPool;

/*reads a txt file and places it into a buffer so it may be encrypted*/
size_t readText(FILE* file, char text[], size_t maxTextSize)
{
    int c;
    int i = 0;
    while ((c = fgetc(file)) != EOF && i < maxTextSize) {
        text[i] = c;
        i++;
    }
    if (i == maxTextSize) {
        i--;
    }
    text[i] = '\0';
    return (i);
}

size_t readCipherBook(FILE* file, char text[], size_t maxTextSize)
{
    size_t original = readText(file, text, maxTextSize);
    int n = 0; //n keeps track of where the modified text is up to
    for (int i = 0; i < original; i++) {
        if (isspace(text[i]) == 0) {
            text[n] = text[i];
            n++;
        }
    }
    text[n] = '\0';
    return n;
}

size_t readMessage(FILE* file, char text[], size_t maxTextSize)
{
    size_t original = readText(file, text, maxTextSize);
    int n = 0; //n keeps track of where the modified text is up to
    for (int i = 0; i < original; i++) {
        if (text[i] == '\t') {
            text[n] = 96;
        } else if (text[i] == '\n') {
            text[n] = 97;
        } else if (text[i] >= 32 && text[i] <= 126) {
            text[n] -= 31;
        } else {
            continue;
        }
        n++;
    }
    text[n] = '\0';
    return n;
}

// A function to initialise an AgentPool structure
void initAgentPool(AgentPool* agentPool)
{
    agentPool->size = MAX_NUMBER_AGENTS;
    agentPool->next = 0;
}

Agent* newAgent(AgentPool* agentPool)
{
    if (agentPool->next < agentPool->size) {
        agentPool->next++;
        return &agentPool->pool[agentPool->next-1];
    }
    return NULL;
}

Agent* findAgent(char name[], AgentPool* agentPool)
{
    for (int i = 0; i < agentPool->size; i++) {
        Agent* agentCheck = &agentPool->pool[i];
        if (strncmp(agentCheck->name, name, MAX_AGENTNAME_LENGTH) == 0) {
            return agentCheck;
        }
    }
    return NULL;
}

// A function to delete an agent from an AgentPool
void deleteAgent(Agent* agent, AgentPool* agentPool)
{
    int i;
    int move = 0;
    for (i = 0; i < agentPool->next-1; i++) {
        if (move || &agentPool->pool[i] == agent) {
            move = 1;
            agentPool->pool[i] = agentPool->pool[i+1];
        }
    }

    agentPool->next--;
}

// A function to read a file with agent data in it, adding the agent to a agentlist and returning a reference to the agent
Agent* readAgent(FILE* file, AgentPool* agentPool)
{
    char line[MAX_LINE_LENGTH];
    int successAgentName = 0;
    int successAgentKey = 0;
    Agent* agent = newAgent(agentPool);

    if (fgets(line, MAX_LINE_LENGTH, file) && agent) {
        size_t i;
        for (i = 0; i < strlen(line) && line[i] != ',' && i < MAX_AGENTNAME_LENGTH-1; i++) {
            agent->name[i] = line[i];
        }
        agent->name[i] = '\0';
        while (i < strlen(line) && line[i] != ',') {
            i++;
        }
        if (line[i] == ',' && strlen(agent->name) > 0) {
            i++;
            successAgentName = 1;
            successAgentKey = sscanf(line+i, "%zu", &agent->key) == 1;
        }
    }
    if (agent && !(successAgentName && successAgentKey)) {
        deleteAgent(agent, agentPool);
        agent = NULL;
    }
    return agent;
}

void readAgentName(char agentName[], size_t maxAgentNameLength)
{
    char c;
    size_t i;

    c = getchar();
    for (i = 0; i < maxAgentNameLength-1 && c != '\n'; i++) {
        agentName[i] = c;
        c = getchar();
    }
    agentName[i] = '\0';
}

void encryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength)
{
    int n = agent->key;
    for (int i = 0; i < messageLength; i++) {
        if (n == bookLength) {
            n = 0;
        }
        message[i] = ((message[i] + book[n]) % 98);
        n++;
    }
}

void decryptMessage(char book[], size_t bookLength, Agent* agent, char message[], size_t messageLength)
{
    int n = agent->key;
    for (int i = 0; i < messageLength; i++) {
        if (n == bookLength) {
            n = 0;
        }
        message[i] = (message[i] - book[n]);
        while (message[i] < 0) {
            message[i] += 98;
        }
        if ((message[i] % 98) == 97) {
            message[i] = 10;
        } else if ((message[i] % 98) == 96) {
            message[i] = 9;
        } else {
            message[i] = (message[i] % 98) + 31;
            if (message[i] < 32) {
                message[i] += 98;
            }
        }
        n++;
    }
}

int main(void)
{
    char filename[80] = "";
    char agentname[MAX_AGENTNAME_LENGTH] = "";
    FILE* file = NULL;
    char book[MAX_TEXTFILE_SIZE] = "";
    char message[MAX_TEXTFILE_SIZE] = "";
    size_t bookLength = 0;
    size_t messageLength = 0;
    AgentPool agentPool;
    Agent* agent = NULL;
    
    // Read in the cipher book
    scanf("%80s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    bookLength = readCipherBook(file, book, MAX_TEXTFILE_SIZE);
    fclose(file);
    
    // Read in the message
    scanf("%80s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    messageLength = readMessage(file, message, MAX_TEXTFILE_SIZE);
    fclose(file);
    
    scanf("%80s", filename);
    initAgentPool(&agentPool);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    while (!feof(file)) {
        readAgent(file, &agentPool);
    }
    fclose(file);
    
    getchar();
    readAgentName(agentname, MAX_AGENTNAME_LENGTH);
    agent = findAgent(agentname, &agentPool);
    if (agent != NULL) {
        encryptMessage(book, bookLength, agent, message, messageLength);
        printf("Secret message is: ");
        for(size_t i=0; i < messageLength; i++) {
            printf("%d, ", message[i]);
        }
        decryptMessage(book, bookLength, agent, message, messageLength);
        printf("\nDecrypted message is: %s\n", message);
    } else {
        printf("No Agent found by the name %s\n", agentname);
    }
    return 0;
}
