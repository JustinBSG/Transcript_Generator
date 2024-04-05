#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

#include "../Inc/transcript.hpp"

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
    /**
     * @brief Construct a new Generator object, default constructor
     * 
     */
    Generator() = default;

    /**
     * @brief Destroy the Generator object
     * 
     */
    ~Generator();

    void start();
    void insert_data(Transcript*& current);
    void read_csv(Transcript*& current);
    void generate_csv(Transcript*& current);
    void modify_csv(Transcript*& current);
    void print_terminal(Transcript*& current);
    void save_transcript(Transcript*& current);
    void restart(Transcript*& current);
    void switch_transcript(Transcript*& current);
    void end(Transcript*& current);
    void remove_transcript(int index);

    void auto_input_period_semesters(BST<Semester>& semesters, int num_year, std::string admit_date);
    bool contain(Transcript* current);

    void print_test(const Transcript* const current) const;
};

#endif  // GENERATOR_HPP