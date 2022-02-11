#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	// -------------------------------

	// all points to be drawn for triangles
	std::vector<vector3> pts;

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisions));

	// for how many triangles are making up this circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fRadius, sin(degree) * a_fRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		pts.push_back(pt);
	}

	// then, draw all points
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(vector3(0.0f, 0.0f, 0.0f),
			pts[(i + 1) % a_nSubdivisions],
			pts[i]);
	}

	// now that circle is drawn, connect all to point at height
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(pts[i],
			pts[(i + 1) % a_nSubdivisions],
			vector3(0.0f, 0.0f, a_fHeight));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	// -------------------------------

	// all points to be drawn for triangles
	std::vector<vector3> pts;

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisions));

	// for how many triangles are making up this circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fRadius, sin(degree) * a_fRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		pts.push_back(pt);
	}

	// then, draw all points
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(vector3(0.0f, 0.0f, 0.0f), 
			   pts[i],
			   pts[(i + 1) % a_nSubdivisions]);
	}

	// then, draw all points but higher up (by height given)
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(vector3(0.0f, 0.0f, 0.0f - a_fHeight),
			   vector3(pts[(i + 1) % a_nSubdivisions].x, pts[(i + 1) % a_nSubdivisions].y, pts[(i + 1) % a_nSubdivisions].z - a_fHeight),
			   vector3(pts[i].x, pts[i].y, pts[i].z - a_fHeight));
	}

	// Connect the circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// use points from top and bottom circle to draw quad
		AddQuad(pts[(i + 1) % a_nSubdivisions],
			    pts[i],
			    vector3(pts[(i + 1) % a_nSubdivisions].x, pts[(i + 1) % a_nSubdivisions].y, pts[(i + 1) % a_nSubdivisions].z - a_fHeight), 
			    vector3(pts[i].x, pts[i].y,pts[i].z - a_fHeight) );
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	// -------------------------------

	// DEGREES

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisions));

	// OUTER

	// all points to be drawn Outer
	std::vector<vector3> ptsOut;

	// for how many divisions are making up this Tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fInnerRadius, sin(degree) * a_fInnerRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		ptsOut.push_back(pt);
	}

	// INNER

	// all points to be drawn Inner
	std::vector<vector3> ptsIn;

	// for how many divisions are making up this Tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fOuterRadius, sin(degree) * a_fOuterRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		ptsIn.push_back(pt);
	}

	// bottom ring
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vector3(ptsOut[(i + 1) % a_nSubdivisions].x, ptsOut[(i + 1) % a_nSubdivisions].y, ptsOut[(i + 1) % a_nSubdivisions].z),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z),
			ptsIn[(i + 1) % a_nSubdivisions],
			ptsIn[i]);
	}

	// top ring
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vector3(ptsIn[(i + 1) % a_nSubdivisions].x, ptsIn[(i + 1) % a_nSubdivisions].y, ptsIn[(i + 1) % a_nSubdivisions].z - a_fHeight),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z - a_fHeight),
			vector3(ptsOut[(i + 1) % a_nSubdivisions].x, ptsOut[(i + 1) % a_nSubdivisions].y, ptsOut[(i + 1) % a_nSubdivisions].z - a_fHeight),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z - a_fHeight));		
	}

	// inner tall
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vector3(ptsOut[(i + 1) % a_nSubdivisions].x, ptsOut[(i + 1) % a_nSubdivisions].y, ptsOut[(i + 1) % a_nSubdivisions].z - a_fHeight),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z - a_fHeight),
			vector3(ptsOut[(i + 1) % a_nSubdivisions].x, ptsOut[(i + 1) % a_nSubdivisions].y, ptsOut[(i + 1) % a_nSubdivisions].z  ),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z));
	}

	// outer tall
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vector3(ptsIn[(i + 1) % a_nSubdivisions].x, ptsIn[(i + 1) % a_nSubdivisions].y, ptsIn[(i + 1) % a_nSubdivisions].z),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z),
			vector3(ptsIn[(i + 1) % a_nSubdivisions].x, ptsIn[(i + 1) % a_nSubdivisions].y, ptsIn[(i + 1) % a_nSubdivisions].z - a_fHeight),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z - a_fHeight));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	// GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// differences in radius
	GLfloat a_fRad = a_fOuterRadius - a_fInnerRadius;

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisionsA));

	// all points to be drawn for CIRCLES
	std::vector<vector3> ptsCircle;

	// origins of CIRCLES
	std::vector<vector3> originCircle;

	// all points to be drawn for QUADS
	std::vector<std::vector<vector3>> circles;

	// make subA circle
	for (int x = 0; x < a_nSubdivisionsA; x++)
	{
		// GET CIRCLE POINTS

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fRad, sin(degree) * a_fRad, 0.0f);

		// add to list of all points
		ptsCircle.push_back(pt);
	}

	// tranform each point once
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		// transform
		matrix4 transform = glm::translate(vector3(a_fInnerRadius, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, addingDegrees * i, vector3(0.0f, 1.0f, 0.0f));

		// origin for this tri
		vector3 ptOrigin = transform * vector4(ZERO_V3, 1.0f);

		// store it
		originCircle.push_back(ptOrigin);

		// Apply tansformation like so: vec3 = mat4 * vec4(vec3,1.0f));
		vector3 ptTransformed = transform * vector4(ptsCircle[i], 1.0f);

		// add transformed vector3 to list
		ptsCircle.push_back(ptTransformed);
	}

	//make circle from sub store in vec
	//transform it every time store in vec of vec
	//draw that vec

	// then, draw all circle points
	for (int i = a_nSubdivisionsA; i < (a_nSubdivisionsA * a_nSubdivisionsA); i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri( originCircle[i % a_nSubdivisionsA],
				ptsCircle[i % a_nSubdivisionsA],
			    ptsCircle[(i + 1) % a_nSubdivisionsA]);
	}


	// APPLY ROTATE TO CIRCLES AND CONNECT VIA QUAD

	    /*
		* 
		matrix4 transform = glm::translate(vector3(a_fInnerRadius, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, addingDegrees * y, vector3(0.0f, 1.0f, 0.0f));
		* 
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fInnerRadius, sin(degree) * a_fInnerRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		ptsOut.push_back(vector4(pt, 1.0f));

		for (int y = 0; y < a_nSubdivisionsA; y++)
		{
			matrix4 transform = glm::translate(vector3(a_fInnerRadius, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, addingDegrees * y, vector3(0.0f, 1.0f, 0.0f));

			vector4 quad = vector4( vector3(ptsOut[(x + 1) % a_nSubdivisionsA].x, ptsOut[(x + 1) % a_nSubdivisionsA].y, ptsOut[(x + 1) % a_nSubdivisionsA].z),
				vector3(ptsOut[x].x, ptsOut[x].y, ptsOut[x].z),
				ptsIn[(x + 1) % a_nSubdivisionsA],
				ptsIn[x]);

			vector4 quadRot = quad * transform;

			AddQuad(quadRot);
		}

	// for how many divisions are making up this Tube
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fInnerRadius, sin(degree) * a_fInnerRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		ptsOut.push_back(vector4(pt, 1.0f));
	}

	// for how many divisions are making up this Tube
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fOuterRadius, sin(degree) * a_fOuterRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		ptsIn.push_back(pt);
	}

	// bottom ring
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		AddQuad(vector3(ptsOut[(i + 1) % a_nSubdivisionsA].x, ptsOut[(i + 1) % a_nSubdivisionsA].y, ptsOut[(i + 1) % a_nSubdivisionsA].z),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z),
			ptsIn[(i + 1) % a_nSubdivisionsA],
			ptsIn[i]);
	}

	// top ring
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		AddQuad(vector3(ptsIn[(i + 1) % a_nSubdivisionsA].x, ptsIn[(i + 1) % a_nSubdivisionsA].y, ptsIn[(i + 1) % a_nSubdivisionsA].z - height),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z - height),
			vector3(ptsOut[(i + 1) % a_nSubdivisionsA].x, ptsOut[(i + 1) % a_nSubdivisionsA].y, ptsOut[(i + 1) % a_nSubdivisionsA].z - height),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z - height));
	}

	// inner tall bottom
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		AddQuad(vector3(ptsOut[(i + 1) % a_nSubdivisionsA].x, ptsOut[(i + 1) % a_nSubdivisionsA].y, ptsOut[(i + 1) % a_nSubdivisionsA].z - height),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z - height),
			vector3(ptsOut[(i + 1) % a_nSubdivisionsA].x, ptsOut[(i + 1) % a_nSubdivisionsA].y, ptsOut[(i + 1) % a_nSubdivisionsA].z  ),
			vector3(ptsOut[i].x, ptsOut[i].y, ptsOut[i].z));
	}

	// outer tall bottom
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		AddQuad(vector3(ptsIn[(i + 1) % a_nSubdivisionsA].x, ptsIn[(i + 1) % a_nSubdivisionsA].y, ptsIn[(i + 1) % a_nSubdivisionsA].z),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z),
			vector3(ptsIn[(i + 1) % a_nSubdivisionsA].x, ptsIn[(i + 1) % a_nSubdivisionsA].y, ptsIn[(i + 1) % a_nSubdivisionsA].z - height),
			vector3(ptsIn[i].x, ptsIn[i].y, ptsIn[i].z - height));
	}
	*/

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}

	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisions));

	// all points to be drawn for CIRCLES
	std::vector<vector3> ptsCircle;

	// making points
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		// set rotation for this circle
		matrix4 rot = glm::rotate(IDENTITY_M4, addingDegrees * x, vector3(0.0f, 1.0f, 0.0f));

		for (int y = 0; y < a_nSubdivisions; y++)
		{
			// make points for this circle:

			// increment degree to meet next subdivision
			degree += addingDegrees;

			// new point based on degree, x and y are cos and sin based respectively
			vector3 pt = vector3(cos(degree), sin(degree), 0.0f);

			// apply rotation
			pt = rot * vector4(pt, 1.0f);

			// add to list of all points
			ptsCircle.push_back(pt);
		}
	}

	// then, draw all circle points
	for (int i = 0; i < a_nSubdivisions * a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(ZERO_V3,
			   ptsCircle[i],
			   ptsCircle[(i + 1) % a_nSubdivisions]);
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::AddCircle(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	// all points to be drawn for triangles
	std::vector<vector3> pts;

	// start at 0 degrees for first triangle
	GLfloat degree = 0;

	// how many degrees need to be added for finding next pt (greatlyy depends on subdivions)
	GLfloat addingDegrees = static_cast<GLfloat>(2.0 * 3.1459 / static_cast<GLfloat>(a_nSubdivisions));

	// for how many triangles are making up this circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// new point based on degree, x and y are cos and sin based respectively
		vector3 pt = vector3(cos(degree) * a_fRadius, sin(degree) * a_fRadius, 0.0f);

		// increment degree to meet next subdivision
		degree += addingDegrees;

		// add to list of all points
		pts.push_back(pt);
	}

	// then, draw all points
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// first point is "origin", point two is last point, point three is next point ahead 
		AddTri(vector3(0.0f, 0.0f, 0.0f),
			pts[i],
			pts[(i + 1) % a_nSubdivisions]);
	}
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}