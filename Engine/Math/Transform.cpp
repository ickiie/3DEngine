#include "Transform.h"

namespace nc {

	void Transform::Update()
	{
		glm::mat4 mxs = glm::scale(scale);

		//glm::mat4 mxr;
		//mxr.Rotate(rotation);

		glm::mat4 mxt = glm::translate(position);

		matrix = mxs * mxt;
	}

	void Transform::Update(const glm::mat4& mx)
	{
		glm::mat4 mxs = glm::scale(localScale);

		//glm::mat4 mxr;
		//mxr.Rotate(localRotation);

		glm::mat4 mxt = glm::translate(localPosition);

		matrix = mxs * mxt * mx;

		//position = matrix.GetTranslate();
		//rotation = matrix.GetRotation();
		//scale = matrix.GetScale();
	}

	bool Transform::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool Transform::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);

		return true;
	}


	/*void Transform::Update() {

		Matrix33 mxs;
		mxs.Scale(scale);

		Matrix33 mxr;
		mxr.Rotate(rotation);

		Matrix33 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt;
	}

	void Transform::Update(const Matrix33& mx) {

		Matrix33 mxs;
		mxs.Scale(localScale);

		Matrix33 mxr;
		mxr.Rotate(localRotation);

		Matrix33 mxt;
		mxt.Translate(localPosition);

		matrix = mxs * mxr * mxt * mx;

		position = matrix.GetTranslate();
		rotation = matrix.GetRotation();
		scale = matrix.GetScale();
	}
	bool Transform::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool Transform::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);


		return true;
	}*/
}