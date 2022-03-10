#ifndef CARETAKER_H_
#define CARETAKER_H_

#include <memory>
#include "Memento.h"
#include "Originator.h"

class Command {
 public:
    explicit Command(Editor* e) : editor_(e) {}
    void makeBackup() {
        backup_ = editor_->createSnapshot();
    }
    void undo() {
        if (backup_) {
            editor_->resotre(backup_);
        }
    }

 private:
    Editor *editor_;
    std::shared_ptr<Snapshot> backup_;
};

#endif  // CARETAKER_H_