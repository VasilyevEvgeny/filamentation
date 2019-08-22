//
// Created by vasilyev on 21.08.2019.
//

#ifndef FILAMENTATION_POSTPROCESSORDISPERSION_H
#define FILAMENTATION_POSTPROCESSORDISPERSION_H

#include "postprocessor/postprocessor.h"

class PostprocessorDispersion : public Postprocessor {
public:
    PostprocessorDispersion();

    explicit PostprocessorDispersion(ConfigManager& _config_manager);

    ~PostprocessorDispersion();

    void go(DirManager& _dir_manager,
            std::shared_ptr<Logger>& _logger) override;

};


#endif //FILAMENTATION_POSTPROCESSORDISPERSION_H
