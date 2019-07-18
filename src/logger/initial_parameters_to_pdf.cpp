//
// Created by vasilyev on 04.07.2019.
//

#include <fstream>
#include <cstdlib>

#include "logger.h"

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::add_start(std::string& tex_file_data) {

    tex_file_data += R"(
\documentclass[10pt]{extarticle}
\usepackage[left=2cm, right=2cm, top=2cm, bottom=2cm]{geometry}
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

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::add_end(std::string& tex_file_data) {
    tex_file_data += R"(
\end{tabular}
\end{center}
\end{document})";
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<size_t>& params) {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0]);
    }
    else if (params.size() == 2) {
        sprintf(buffer, str.c_str(), params[0], params[1]);
    }

    tex_file_data += std::string(buffer);
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params) {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0]);
    }
    else if (params.size() == 2) {
        sprintf(buffer, str.c_str(), params[0], params[1]);
    }
    else if (params.size() == 3) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2]);
    }
    else if (params.size() == 6) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5]);
    }
    else if (params.size() == 10) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5], params[6],
                params[7], params[8], params[9]);
    }
    else if (params.size() == 15) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3],
                params[4], params[5], params[6], params[7],
                params[8], params[9], params[10], params[11],
                params[12], params[13], params[14]);
    }

    tex_file_data += std::string(buffer);
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params) {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0].c_str());
    }
    else if (params.size() == 2) {
        sprintf(buffer, str.c_str(), params[0].c_str(), params[1].c_str());
    }

    tex_file_data += std::string(buffer);
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
void Logger<PulsedBeam<Medium>, Processor>::save_initial_parameters_to_pdf(bool delete_tmp_files, bool delete_tex_file) {

    std::string tex_file_data;

    std::string tex_file_name = "parameters";
    std::string path = manager.current_results_dir;
    std::string tex_file_path = path + "/" + tex_file_name + ".tex";




    //
    //  START
    //

    add_start(tex_file_data);



    //
    //  EQUATION
    //

    std::string equation = "no equation yet";

    std::string equation_data = R"(
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\textbf{EQUATION}} \tabularnewline
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\[ %s \]} \tabularnewline
\midrule[2pt]
)";
    std::vector<std::string> equation_params = {equation};

    Logger::add_to_tex_file_data(tex_file_data, equation_data, equation_params);


    //
    //  INITIAL CONDITION
    //

    std::string initial = R"(A(r,0) = A_0 \biggl( \frac{r}{r_0} \biggr)^M \exp \biggl\{ -\frac{r^2}{2r_0^2} \biggr\} \exp \biggl\{ -\frac{t^2}{2t_0^2} \biggr\})";

    std::string initial_data = R"(
\multicolumn{3}{M{15cm}}{\textbf{INITIAL CONDITION}} \tabularnewline
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\[ %s \]} \tabularnewline
\midrule[2pt]
)";
    std::vector<std::string> initial_params = {initial};

    Logger::add_to_tex_file_data(tex_file_data, initial_data, initial_params);


    //
    //  Sellmeyer formula
    //

    std::string sellmeyer_data = R"(
\multicolumn{3}{M{15cm}}{\textbf{SELLMEYER FORMULA}} \tabularnewline
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\[ n(\lambda) =
\sqrt{ 1 + \frac{%.10f \lambda^2}{\lambda^2 - %.10f^2} +
           \frac{%.10f \lambda^2}{\lambda^2 - %.10f^2} +
           \frac{%.10f \lambda^2}{\lambda^2 - %.10f^2}} \]} \tabularnewline
\midrule[2pt]
\end{tabular}
)";
    std::vector<double> sellmeyer_params = {pulsed_beam->medium->C_1,
                                            pulsed_beam->medium->lambda_1 * 1e6,
                                            pulsed_beam->medium->C_2,
                                            pulsed_beam->medium->lambda_2 * 1e6,
                                            pulsed_beam->medium->C_3,
                                            pulsed_beam->medium->lambda_3 * 1e6};

    Logger::add_to_tex_file_data(tex_file_data, sellmeyer_data, sellmeyer_params);

    //
    //  MEDIUM
    //

    std::string medium_data_1 = R"(
\begin{tabular}{M{5cm}M{5cm}M{5cm}}
\midrule[2pt]
\multicolumn{3}{M{15cm}}{\textbf{MEDIUM}} \tabularnewline
\midrule[2pt]
material & %s & -- \tabularnewline
\hline
)";
    std::vector<std::string> medium_params_1 = {pulsed_beam->medium->info};
    Logger::add_to_tex_file_data(tex_file_data, medium_data_1, medium_params_1);


    std::string medium_data_2 = R"(
$n_0$ & %05.4f & -- \tabularnewline
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
$\nu_{ei}$ & %.1f & THz \tabularnewline
\hline
$\beta$ & %.1f & THz \tabularnewline
\hline
$U_i$ & %3.1f & eV \tabularnewline
\hline
$K$ & %.0f & -- \tabularnewline
\hline
$\delta$ & %.1f & cm$^{-1}$ \tabularnewline
\midrule[2pt]
)";
    std::vector<double> medium_params_2 = {pulsed_beam->medium->n_0,
                                           pulsed_beam->medium->k_0 * 1e-3,
                                           pulsed_beam->medium->k_1 * 1e12,
                                           pulsed_beam->medium->k_2 * 1e27,
                                           pulsed_beam->medium->n_2 * 1e20,
                                           pulsed_beam->medium->g,
                                           pulsed_beam->medium->Omega_R * 1e-12,
                                           pulsed_beam->medium->tau_k * 1e15,
                                           pulsed_beam->medium->conv_window * 1e15,
                                           pulsed_beam->medium->N_0 * 1e-28,
                                           pulsed_beam->medium->v_ei * 1e-12,
                                           pulsed_beam->medium->beta * 1e-12,
                                           pulsed_beam->medium->U_i_in_eV,
                                           (double)pulsed_beam->medium->K,
                                           pulsed_beam->medium->delta * 1e2};

    Logger::add_to_tex_file_data(tex_file_data, medium_data_2, medium_params_2);


    //
    //  PULSED BEAM
    //

    std::string pulsed_beam_data_1 = R"(
\multicolumn{3}{M{15cm}}{\textbf{PULSED BEAM}} \tabularnewline
\midrule[2pt]
space distribution & %s & -- \tabularnewline
\hline
)";
    std::vector<std::string> pulsed_beam_params_1 = {pulsed_beam->info};

    Logger::add_to_tex_file_data(tex_file_data, pulsed_beam_data_1, pulsed_beam_params_1);


    std::string pulsed_beam_data_2 = R"(
$M$ & %d & -- \tabularnewline
\hline
$m$ & %d & -- \tabularnewline
\hline
)";
    std::vector<std::size_t> pulsed_beam_params_2 = {pulsed_beam->M,
                                                     pulsed_beam->m};

    Logger::add_to_tex_file_data(tex_file_data, pulsed_beam_data_2, pulsed_beam_params_2);



    std::string pulsed_beam_data_3 = R"(
$r_0$ & %.1f & $\mu$m \tabularnewline
\hline
$\lambda$ & %.1f & nm \tabularnewline
\hline
$z_{diff}$ & %.2f & cm \tabularnewline
\hline
$P_0 / P_{cr}$ & %.2f & -- \tabularnewline
\hline
$P_{cr} / P_G$ & %.2f & -- \tabularnewline
\hline
$P_G$ & %.2f & MW \tabularnewline
\hline
$P_0$ & %.2f & MW \tabularnewline
\hline
$I_{max}(z=0) / I_0$ & %.2f & -- \tabularnewline
\hline
$I_0$ & %.4f & TW/cm$^2$ \tabularnewline
\hline
$E_0$ & %.2f & $\mu$J \tabularnewline
\midrule[2pt]
)";
    std::vector<double> pulsed_beam_params_3 = {pulsed_beam->r_0 * 1e6,
                                                pulsed_beam->lambda_0 * 1e9,
                                                pulsed_beam->z_diff * 1e2,
                                                pulsed_beam->p_0_to_p_cr,
                                                pulsed_beam->p_cr_to_p_g,
                                                pulsed_beam->p_g * 1e-6,
                                                pulsed_beam->p_0 * 1e-6,
                                                pulsed_beam->max_intensity(pulsed_beam->i_0),
                                                pulsed_beam->i_0 * 1e-16,
                                                pulsed_beam->e_0 * 1e6};

    Logger::add_to_tex_file_data(tex_file_data, pulsed_beam_data_3, pulsed_beam_params_3);

    //
    //  GRID
    //

    std::string grid_data_1 = R"(
\multicolumn{3}{M{15cm}}{\textbf{GRID}} \tabularnewline
\midrule[2pt]
$r_{max}$ & %.1f & $\mu$m \tabularnewline
\hline
)";
    std::vector<double> grid_params_1 = {pulsed_beam->r_max * 1e6};

    Logger::add_to_tex_file_data(tex_file_data, grid_data_1, grid_params_1);


    std::string grid_data_2 = R"(
$n_{r}$ & %d & -- \tabularnewline
\hline
)";
    std::vector<size_t> grid_params_2 = {pulsed_beam->n_r};

    Logger::add_to_tex_file_data(tex_file_data, grid_data_2, grid_params_2);


    std::string grid_data_3 = R"(
$h_r$ & %.1f & $\mu$m \tabularnewline
\hline
$t_{max}$ & %.1f & fs \tabularnewline
\hline
)";
    std::vector<double> grid_params_3 = {pulsed_beam->dr * 1e6,
                                         pulsed_beam->t_max * 1e15};

    Logger::add_to_tex_file_data(tex_file_data, grid_data_3, grid_params_3);


    std::string grid_data_4 = R"(
$n_t$ & %d & -- \tabularnewline
\hline
)";
    std::vector<size_t> grid_params_4 = {pulsed_beam->n_t};

    Logger::add_to_tex_file_data(tex_file_data, grid_data_4, grid_params_4);


    std::string grid_data_5 = R"(
$h_t$ & %.1f & fs \tabularnewline
\midrule[2pt]
)";
    std::vector<double> grid_params_5 = {pulsed_beam->dt * 1e15};

    Logger::add_to_tex_file_data(tex_file_data, grid_data_5, grid_params_5);

    /*
     * TRACK
     */

    std::string track_data = R"(
\multicolumn{3}{M{15cm}}{\textbf{TRACK}} \tabularnewline
\midrule[2pt]
$n_z$ & %.0f & -- \tabularnewline
\hline
$h_z(z=0)$ & %.1f & $\mu$m \tabularnewline
\midrule[2pt]
)";
    std::vector<double> track_params = {track_info["n_z"],
                                        track_info["dz"] * 1e6};

    Logger::add_to_tex_file_data(tex_file_data, track_data, track_params);


    //
    //  END
    //

    add_end(tex_file_data);

    // make tex file
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

template class Logger<Gauss<SiO2>, Processor>;
template class Logger<Gauss<CaF2>, Processor>;
template class Logger<Gauss<LiF>, Processor>;
template class Logger<Ring<SiO2>, Processor>;
template class Logger<Ring<CaF2>, Processor>;
template class Logger<Ring<LiF>, Processor>;
template class Logger<Vortex<SiO2>, Processor>;
template class Logger<Vortex<CaF2>, Processor>;
template class Logger<Vortex<LiF>, Processor>;

template class Logger<Gauss<SiO2>, ProcessorDiffraction>;
template class Logger<Gauss<CaF2>, ProcessorDiffraction>;
template class Logger<Gauss<LiF>, ProcessorDiffraction>;
template class Logger<Ring<SiO2>, ProcessorDiffraction>;
template class Logger<Ring<CaF2>, ProcessorDiffraction>;
template class Logger<Ring<LiF>, ProcessorDiffraction>;
template class Logger<Vortex<SiO2>, ProcessorDiffraction>;
template class Logger<Vortex<CaF2>, ProcessorDiffraction>;
template class Logger<Vortex<LiF>, ProcessorDiffraction>;