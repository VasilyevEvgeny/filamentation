//
// Created by vasilyev on 30.06.2019.
//

#include <fstream>
#include <cstdlib>

#include "Logger.h"

Logger::Logger() = default;

Logger::~Logger() = default;

void Logger::save_initial_parameters(PulsedBeam& pulsed_beam, std::string& path,
        bool delete_tmp_files, bool delete_tex_file) const {

    std::string tex_file_name = "parameters";
    std::string tex_file_path = path + "/" + tex_file_name + ".tex";

    std::string tex_file_data =
        "\\documentclass[10pt]{extarticle}\n"
        "\\usepackage[left=2cm, right=2cm, top=1cm, bottom=1cm]{geometry}\n"
        "\\usepackage{array}\n"
        "\\newcolumntype{P}[1]{>{\\centering\\arraybackslash}p{#1}}\n"
        "\\newcolumntype{M}[1]{>{\\centering\\arraybackslash}m{#1}}\n"
        "\\usepackage[table]{xcolor}\n"
        "\\usepackage{booktabs}\n"
        "\\renewcommand{\\arraystretch}{1.2}\n"
        "\\setlength{\\tabcolsep}{0pt}\n"
        "\n"
        "\\begin{document}\n"
        "\\pagestyle{empty}\n"
        "\\begin{center}\n"
        //"\\begin{tabular}{M{5cm}M{5cm}M{5cm}}"
        //"\\multicolumn{3}{M{15cm}}{\\textbf{BEAM}} \\tabularnewline\n"
        //"\\midrule[2pt]\n"
        //(std::ostringstream()).str()"distribution & %s & -- \\tabularnewline\n"
        //"\\hline"
        //"\\end{tabular}"
        ""
        "Hello, world!!\n"
        "\\end{center}\n"
        "\\end{document}\n";

    std::ofstream f(tex_file_path);
    f << tex_file_data;
    f.close();

    // compile pdf
    std::string compile_string = "pdflatex -quiet -interaction=nonstopmode " + tex_file_path + " -output-directory " + path;
    std::system(compile_string.c_str());

    // delete tmp files
    if (delete_tmp_files) {
        std::string filename = path + "/" + tex_file_name + ".";
        for (const auto& e : {"aux", "log"}) {
            std::remove((filename + e).c_str());
        }
    }

    // delete tmp files
    if (delete_tex_file) {
        std::remove(tex_file_path.c_str());
    }
}