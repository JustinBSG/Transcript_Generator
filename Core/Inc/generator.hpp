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

    /**
     * @brief Start the Program
     *
     */
    void start();

    /**
     * @brief Input data by user
     *
     * @param current
     */
    void insert_data(Transcript*& current);

    /**
     * @brief Input data from CSV file
     *
     * @param current
     */
    void read_csv(Transcript*& current);

    /**
     * @brief Generate CSV file into Output/
     * 
     */
    void generate_csv();

    /**
     * @brief Modify data that inside CSV file
     *
     * @param current
     */
    void modify_csv(Transcript* current);

    /**
     * @brief Generate transcript into terminal
     *
     * @param current
     */
    void print_all(Transcript* current);

    /**
     * @brief Make a new transcript
     *
     * @param current
     */
    void restart(Transcript*& current);

    /**
     * @brief Switch to anther transcript
     * 
     * @param current 
     */
    void switch_transcript(Transcript*& current);

    /**
     * @brief Release all dellocated memory
     *
     * @param current
     */
    void end(Transcript*& current);

    /**
     * @brief Save current transcript into the vector of transcript
     * 
     * @param current 
     */
    void save(Transcript* current);

    /**
     * @brief Return number of transcript
     *
     * @return int
     */
    int get_num_transcript() const;

    /**
     * @brief Insert other transcript
     *
     * @param other_transcript
     */
    void insert_transcript(Transcript* other_transcript);

    /**
     * @brief Remove transcript according to given index
     *
     * @param index
     */
    void remove_transcript(int index);
};

#endif