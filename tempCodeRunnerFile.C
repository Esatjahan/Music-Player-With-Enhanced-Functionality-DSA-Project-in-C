#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data structure definitions
struct Song {
    char title[100];
    char artist[100];
};

struct Node {
    struct Song song;
    struct Node* next;
};

struct Playlist {
    struct Node* head;
};

struct Stack {
    struct Node* top;
};

// Function prototypes
void initPlaylist(struct Playlist* playlist);
void initStack(struct Stack* stack);
void addSong(struct Playlist* playlist, struct Song newSong);
void displayPlaylist(struct Playlist* playlist);
void playSong(struct Playlist* playlist, struct Stack* history);
void displayHistory(struct Stack* history);
void sortPlaylist(struct Playlist* playlist);
void searchPlaylist(struct Playlist* playlist, const char* searchTitle);
void addToPlaylistFromFile(struct Playlist* playlist, const char* filename);
void savePlaylistToFile(struct Playlist* playlist, const char* filename);
int getTotalSongs(struct Playlist* playlist);
void removeFromPlaylist(struct Playlist* playlist, int position);
void clearPlaylist(struct Playlist* playlist);
void undoPlayedSong(struct Playlist* playlist, struct Stack* history);

int main() {
    struct Playlist playlist;
    struct Stack history;
    initPlaylist(&playlist);
    initStack(&history);

    int choice;
    char searchTitle[100];
    char filename[100];
    struct Song newSong;

    do {
        printf("\nMusic Player Menu:\n");
        printf("1. Add a song\n");
        printf("2. Display Playlist\n");
        printf("3. Play a song\n");
        printf("4. Display Recently Played\n");
        printf("5. Sort Playlist\n");
        printf("6. Search Playlist\n");
        printf("7. Add songs from a file\n");
        printf("8. Save Playlist to a file\n");
        printf("9. Delete song\n");
        printf("10. Clear Playlist\n");
        printf("11. Undo\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf("%s", newSong.title);
                printf("Enter artist name: ");
                scanf("%s", newSong.artist);
                addSong(&playlist, newSong);
                break;
            case 2:
                displayPlaylist(&playlist);
                break;
            case 3:
                playSong(&playlist, &history);
                break;
            case 4:
                displayHistory(&history);
                break;
            case 5:
                sortPlaylist(&playlist);
                printf("Playlist sorted successfully.\n");
                break;
            case 6:
                printf("Enter song title to search: ");
                scanf("%s", searchTitle);
                searchPlaylist(&playlist, searchTitle);
                break;
            case 7:
                printf("Enter filename: ");
                scanf("%s", filename);
                addToPlaylistFromFile(&playlist, filename);
                printf("Songs added from file.\n");
                break;
            case 8:
                printf("Enter filename to save: ");
                scanf("%s", filename);
                savePlaylistToFile(&playlist, filename);
                printf("Playlist saved to file.\n");
                break;
            case 9:
                printf("Enter position to delete: ");
                int position;
                scanf("%d", &position);
                removeFromPlaylist(&playlist, position);
                break;
            case 10:
                clearPlaylist(&playlist);
                printf("Playlist cleared.\n");
                break;
            case 11:
                undoPlayedSong(&playlist, &history);
                break;
            case 12:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 12);

    return 0;
}

// Function definitions
void initPlaylist(struct Playlist* playlist) {
    playlist->head = NULL;
}

void initStack(struct Stack* stack) {
    stack->top = NULL;
}

void addSong(struct Playlist* playlist, struct Song newSong) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->song = newSong;
    newNode->next = playlist->head;
    playlist->head = newNode;
}

void displayPlaylist(struct Playlist* playlist) {
    if (playlist->head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Node* current = playlist->head;
    printf("Current Playlist:\n");
    int count = 1;
    while (current != NULL) {
        printf("%d. Title: %s, Artist: %s\n", count, current->song.title, current->song.artist);
        current = current->next;
        count++;
    }
}

void playSong(struct Playlist* playlist, struct Stack* history) {
    if (playlist->head == NULL) {
        printf("Playlist is empty. Cannot play any song.\n");
        return;
    }

    int songChoice;
    printf("Select a song to play (1-%d): ", getTotalSongs(playlist));
    scanf("%d", &songChoice);

    struct Node* current = playlist->head;
    int count = 1;
    while (current != NULL && count < songChoice) {
        current = current->next;
        count++;
    }

    if (count == songChoice && current != NULL) {
        // Play the selected song
        printf("Now Playing: %s by %s\n", current->song.title, current->song.artist);

        // Move the played song to the history
        struct Node* playedSong = current;
        current = current->next;
        playedSong->next = history->top;
        history->top = playedSong;

        // Remove the played song from the playlist
        removeFromPlaylist(playlist, songChoice);
    } else {
        printf("Invalid song choice.\n");
        // Clear input buffer
        while (getchar() != '\n');
    }
}

void displayHistory(struct Stack* history) {
    struct Node* current = history->top;
    while (current != NULL) {
        printf("Title: %s, Artist: %s\n", current->song.title, current->song.artist);
        current = current->next;
    }
}

void sortPlaylist(struct Playlist* playlist) {
    // Implement sorting algorithm (e.g., bubble sort)
}

void searchPlaylist(struct Playlist* playlist, const char* searchTitle) {
    // Implement searching algorithm (e.g., linear search)
}

void addToPlaylistFromFile(struct Playlist* playlist, const char* filename) {
    // Read songs from file and add to the playlist
}

void savePlaylistToFile(struct Playlist* playlist, const char* filename) {
    // Save playlist to file
}

int getTotalSongs(struct Playlist* playlist) {
    int count = 0;
    struct Node* current = playlist->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void removeFromPlaylist(struct Playlist* playlist, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        struct Node* temp = playlist->head;
        playlist->head = temp->next;
        free(temp);
        return;
    }

    struct Node* current = playlist->head;
    int count = 1;
    while (count < position - 1 && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}

void clearPlaylist(struct Playlist* playlist) {
    while (playlist->head != NULL) {
        struct Node* temp = playlist->head;
        playlist->head = temp->next;
        free(temp);
    }
}

void undoPlayedSong(struct Playlist* playlist, struct Stack* history) {
    if (history->top != NULL) {
        // Add the top node of the history stack to the playlist
        struct Node* playedSong = history->top;
        playedSong->next = playlist->head;
        playlist->head = playedSong;

        // Remove the top node from the history stack
        struct Node* temp = history->top;
        history->top = temp->next;
        free(temp);
    }
}
