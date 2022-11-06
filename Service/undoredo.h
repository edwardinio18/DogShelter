#ifndef A14_EDWARDINIO18_UNDOREDO_H
#define A14_EDWARDINIO18_UNDOREDO_H


#include "../Repository/repository.h"
#include "../Repository/userRepository.h"

class UndoRedoAction {
public:
	virtual void undo() = 0;

	virtual void redo() = 0;
};

class UndoRedoAdd : public UndoRedoAction {
private:
	Dog addedDog;
	Repository &repo;
public:
	UndoRedoAdd(const Dog &dog, Repository &newRepo);

	void undo() override;

	void redo() override;
};

class UndoRedoRemove : public UndoRedoAction {
private:
	Dog removedDog;
	Repository &repo;
public:
	UndoRedoRemove(const Dog &dog, Repository &newRepo);

	void undo() override;

	void redo() override;
};

class UndoRedoUpdate : public UndoRedoAction {
private:
	Dog oldDog;
	Dog newDog;
	Repository &repo;
public:
	UndoRedoUpdate(const Dog &oldDog, const Dog &newDog, Repository &newRepo);

	void undo() override;

	void redo() override;
};


#endif //A14_EDWARDINIO18_UNDOREDO_H