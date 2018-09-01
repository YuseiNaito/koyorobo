#ifndef KOYO_DATA_LIST_H
#define KOYO_DATA_LIST_H

namespace koyo {
	namespace data_list {
		// for input
		struct signal {
			double vartical;   // �c����
			double horizontal; // ��]����
			bool button0;      // �{�^��
		};

		// for output
		struct command {
			double vel;    // ���x
			double omega;  // �p���x
			double weapon; // �U��
		};
	}
}

#endif