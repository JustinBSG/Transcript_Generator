#ifndef INC_GENERATOR_HPP
#define INC_GENERATOR_HPP

#include <vector>

#include "transcript.hpp"

#define TERMINAL_MAX_WIDTH 84
#define SPLIT_LINE                                                                  \
  "===============================================================================" \
  "====="
#define TERMINAL_TITLE                                    \
  "******************************* Transcript Generator " \
  "*******************************"

class Generator {
  private:
    std::vector<Transcript*> transcripts;

  public:
    Generator() = default;
    ~Generator();

    void start();
    void insert_csv(Transcript* current);
    void read_csv(Transcript* current);
    void modify_csv(Transcript* current);
    void print_all(Transcript* current);
    void restart(Transcript* current);
    void end(Transcript* current);

    int get_num_transcript() const;

    void insert_transcript(Transcript* other_transcript);
    void remove_transcript(int index);
    void clear_nullptr();
};

#endif