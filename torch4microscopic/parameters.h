#pragma once

//OpenCV�p�C���N���[�h��
//�C���N���[�h�t�@�C���w��
#include <opencv2/opencv.hpp>
//�ÓI�����N���C�u�����̎w��
#include <opencv2/opencv_lib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace parameters
{


	//�e�摜�̖��邳�𕽊�������ۂ̃��[�h
	enum class NormalizeMode
	{
		//�������܂���
		None,
		//�ł��V���v���ȕ��@�𗘗p�B�e�摜���ɍő�P�x�_���ő�l�ɁA�Œ�P�x�_���ŏ��l�Ɏ����Ă����B
		Simple,
		//���`�I�ɖ��邳�͌�������͂��Ȃ̂ŁA����𗘗p���ĕ�����
		ExpDamping
	};

	/*
	//���؂̕��@
	enum class CutbackMode
	{
		//�p�[�Z���e�[�W�ő���
		Relative,
		//��Βl�ő���
		Absolute,
		//�Œ�l��؂�
		CutLowest,
		//�Œ�l���牽������؂�
		CutLowerByPersent
	};
	*/


	class Values
	{
	public:
		double unitsize_depth;
		bool enable_cutback;
		cv::Size window_size;
		bool enable_gblur;
		NormalizeMode normalize_mode;

		Values()
		{
			unitsize_depth = 0.0;
			enable_cutback = false;
			enable_gblur = false;
			window_size = cv::Size(5, 5);
			normalize_mode = NormalizeMode::None;
		}
	};

	
}