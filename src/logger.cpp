//
// Created by vasilyev on 30.06.2019.
//

#include <fstream>
#include <cstdlib>

#include "logger.h"

template<typename Medium>
Logger<Medium>::Logger(PulsedBeam<Medium>& _pulsed_beam) :
  pulsed_beam(_pulsed_beam) {

   tex_file_data = "";
}

template<typename Medium>
Logger<Medium>::~Logger() = default;

template<typename Medium>
void Logger<Medium>::add_start() {

    tex_file_data +=
R"(\documentclass[10pt]{extarticle}
\usepackage[left=2cm, right=2cm, top=1cm, bottom=1cm]{geometry}
\usepackage{array}
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
\newcolumntype{M}[1]{>{\centering\arraybackslash}m{#1}}
\usepackage[table]{xcolor}
\usepackage{booktabs}
\renewcommand{\arraystretch}{1.2}
\setlength{\tabcolsep}{0pt}

\begin{document}
\pagestyle{empty}
\begin{center}
\begin{tabular}{M{5cm}M{5cm}M{5cm}}
)";

}

template<typename Medium>
void Logger<Medium>::add_end() {
    tex_file_data +=
R"(\end{tabular}
\end{center}
\end{document})";
}

template<typename Medium>
void Logger<Medium>::add_to_tex_file_data(std::string& str, std::vector<size_t>& params) {
    char buffer [10000];
    if (params.size() == 2) {
        sprintf(buffer, str.c_str(), params[0], params[1]);
    }

    tex_file_data += std::string(buffer);
}

template<typename Medium>
void Logger<Medium>::add_to_tex_file_data(std::string& str, std::vector<double>& params) {
    char buffer [10000];
    if (params.size() == 3) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2]);
    }
    if (params.size() == 14) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3],
                params[4], params[5], params[6], params[7],
                params[8], params[9], params[10], params[11],
                params[12], params[13]);
    }

    tex_file_data += std::string(buffer);
}

template<typename Medium>
void Logger<Medium>::add_to_tex_file_data(std::string& str, std::vector<std::string>& params) {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0].c_str());
    }
    else if (params.size() == 2) {
        sprintf(buffer, str.c_str(), params[0].c_str(), params[1].c_str());
    }

    tex_file_data += std::string(buffer);
}

template<typename Medium>
void Logger<Medium>::save_initial_parameters(std::string& path, bool delete_tmp_files, bool delete_tex_file) {

    std::string tex_file_name = "parameters";
    std::string tex_file_path = path + "/" + tex_file_name + ".tex";


    //
    //  START
    //

    add_start();



    //
    //  EQUATION
    //

    std::string equation = "no equation yet";

    std::string equation_data =
R"(\midrule[2pt]
\multicolumn{3}{M{15cm}}{\textbf{EQUATION}} \tabularnewline
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\[ %s \]} \tabularnewline
\midrule[2pt]
)";
    std::vector<std::string> equation_params = {equation};

    Logger::add_to_tex_file_data(equation_data, equation_params);


    //
    //  INITIAL CONDITION
    //

    std::string initial = R"(A(r,0) = A_0 \biggl( \frac{r}{r_0} \biggr)^M \exp \biggl\{ -\frac{r^2}{2r_0^2} \biggr\} \exp \biggl\{ -\frac{t^2}{2t_0^2} \biggr\})";

    std::string initial_data =
R"(\multicolumn{3}{M{15cm}}{\textbf{INITIAL CONDITION}} \tabularnewline
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\[ %s \]} \tabularnewline
\midrule[2pt]
)";
    std::vector<std::string> initial_params = {initial};

    Logger::add_to_tex_file_data(initial_data, initial_params);

    //
    //  MEDIUM
    //

    std::string medium_data_1 =
R"(\multicolumn{3}{M{15cm}}{\textbf{MEDIUM}} \tabularnewline
\midrule[2pt]
material & %s & -- \tabularnewline
\hline
)";
    std::vector<std::string> medium_params_1 = {pulsed_beam.medium.info};
    Logger::add_to_tex_file_data(medium_data_1, medium_params_1);


    std::string medium_data_2 =
R"($n_0$ & %05.4f & -- \tabularnewline
\hline
$k_0$ & %07.2f & 1/mm \tabularnewline
\hline
$k_1$ & %07.2f & fs/mm \tabularnewline
\hline
$k_2$ & %05.2f & fs$^2$/mm \tabularnewline
\hline
$n_2$ & %04.2f $\times 10^{-16}$ & cm$^2$/W \tabularnewline
\hline
$g$ & %04.2f & -- \tabularnewline
\hline
$\Omega_R$ & %.1f & THz \tabularnewline
\hline
$\tau_k$ & %.1f & fs \tabularnewline
\hline
$\Delta_t$ & %.1f & fs \tabularnewline
\hline
$N_0$ & %04.2f $\times 10^{22}$ & cm$^{-3}$ \tabularnewline
\hline
$U_i$ & %3.1f & eV \tabularnewline
\hline
$\nu_{ei}$ & %.1f & THz \tabularnewline
\hline
$\beta$ & %.1f & THz \tabularnewline
\hline
$K$ & %.1f & -- \tabularnewline
\midrule[2pt]
)";
    std::vector<double> medium_params_2 = {pulsed_beam.medium.n_0,
                                           pulsed_beam.medium.k_0 * 1e-3,
                                           pulsed_beam.medium.k_1 * 1e12,
                                           pulsed_beam.medium.k_2 * 1e27,
                                           pulsed_beam.medium.n_2 * 1e20,
                                           pulsed_beam.medium.g,
                                           pulsed_beam.medium.Omega_R * 1e-12,
                                           pulsed_beam.medium.tau_k * 1e15,
                                           pulsed_beam.medium.conv_window * 1e15,
                                           pulsed_beam.medium.N_0 * 1e-28,
                                           pulsed_beam.medium.U_i_in_eV,
                                           pulsed_beam.medium.v_ei * 1e-12,
                                           pulsed_beam.medium.beta * 1e-12,
                                           pulsed_beam.medium.K};

    Logger::add_to_tex_file_data(medium_data_2, medium_params_2);


    //
    //  PULSED BEAM
    //

    std::string pulsed_beam_data_1 =
R"(\multicolumn{3}{M{15cm}}{\textbf{PULSED BEAM}} \tabularnewline
\midrule[2pt]
space distribution & %s & -- \tabularnewline
\hline
time distribution & %s & -- \tabularnewline
\hline
)";
    std::vector<std::string> pulsed_beam_params_1 = {pulsed_beam.space_distribution,
                                                     pulsed_beam.time_distribution};

    Logger::add_to_tex_file_data(pulsed_beam_data_1, pulsed_beam_params_1);


    std::string pulsed_beam_data_2 =
R"($M$ & %d & -- \tabularnewline
\hline
$m$ & %d & -- \tabularnewline
\hline
)";
    std::vector<std::size_t> pulsed_beam_params_2 = {pulsed_beam.M,
                                                     pulsed_beam.m};

    Logger::add_to_tex_file_data(pulsed_beam_data_2, pulsed_beam_params_2);



    std::string pulsed_beam_data_3 =
R"($r_0$ & %.1f & $\mu$m \tabularnewline
\hline
$\lambda$ & %.1f & nm \tabularnewline
\hline
$z_{diff}$ & %.1f & cm \tabularnewline
\hline
)";
    std::vector<double> pulsed_beam_params_3 = {pulsed_beam.r_0 * 1e6,
                                                pulsed_beam.lambda_0 * 1e9,
                                                pulsed_beam.z_diff * 1e2};

    Logger::add_to_tex_file_data(pulsed_beam_data_3, pulsed_beam_params_3);

    //
    //  END
    //

    add_end();


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

template class Logger<SiO2>;
template class Logger<CaF2>;
template class Logger<LiF>;