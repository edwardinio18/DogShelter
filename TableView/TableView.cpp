#include "TableView.h"

TableView::TableView(UserServ &userServ, QObject *parent) : userServ{userServ},
															QAbstractTableModel{parent} {}

int TableView::rowCount(const QModelIndex &parent) const {
	return this->userServ.getAllUserService().size();
}

int TableView::columnCount(const QModelIndex &parent) const {
	return 5;
}

QVariant TableView::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int col = index.column();
	auto dogs = this->userServ.getAllUserService();
	Dog dog = dogs[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (col) {
			case 0:
				return QString::fromStdString(dog.getBreed());
			case 1:
				return QString::fromStdString(dog.getName());
			case 2:
				return QString::fromStdString(std::to_string(dog.getAge()));
			case 3:
				return QString::fromStdString(dog.getPhotograph());
			case 4:
				return QString::fromStdString(std::to_string(dog.getIsAdopted()));
			default:
				break;
		}
	}
	return QVariant{};
}

QVariant TableView::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
				case 0:
					return QString("Breed");
				case 1:
					return QString("Name");
				case 2:
					return QString("Age");
				case 3:
					return QString("Photograph");
				case 4:
					return QString("Adopted");
				default:
					break;
			}
		}
	}
	return QVariant();
}

void TableView::propagate() {
	emit layoutChanged();
}
