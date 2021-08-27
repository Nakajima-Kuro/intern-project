#include "AnimationSprite2D.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"

AnimationSprite2D::AnimationSprite2D() :Sprite2D(), m_numFrames(0), m_currentFrame(0), m_frameTime(0.0f), m_currentFrameTime(0.0f), m_isPlaying(true)
{
}

AnimationSprite2D::AnimationSprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, float frameTime)
	: Sprite2D(-1, model, shader, texture), m_numFrames(numFrame), m_currentFrame(0), m_frameTime(frameTime), m_currentFrameTime(0.0f), m_isPlaying(true)
{

}

void AnimationSprite2D::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void AnimationSprite2D::Draw()
{
	if (m_isVisible) {
		if (m_pCamera == nullptr) return;
		glUseProgram(m_pShader->m_program);
		glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

		GLuint iTempShaderVaribleGLID = -1;
		Matrix wvpMatrix;

		wvpMatrix = m_worldMatrix * m_pCamera->GetLookAtCameraMatrix();

		if (m_pTexture != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
			if (m_pShader->m_iTextureLoc[0] != -1)
				glUniform1i(m_pShader->m_iTextureLoc[0], 0);
		}
		else
		{
			iTempShaderVaribleGLID = -1;
			iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
			if (iTempShaderVaribleGLID != -1)
				glUniform4f(iTempShaderVaribleGLID, m_color.x, m_color.y, m_color.z, m_color.w);
		}


		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
		if (iTempShaderVaribleGLID != -1)
		{
			glEnableVertexAttribArray(iTempShaderVaribleGLID);
			glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
		}

		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
		if (iTempShaderVaribleGLID != -1)
		{
			glEnableVertexAttribArray(iTempShaderVaribleGLID);
			glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
		}

		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
		if (iTempShaderVaribleGLID != -1)
			glUniform1f(iTempShaderVaribleGLID, 1.0);

		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_wvpMatrix");
		if (iTempShaderVaribleGLID != -1)
			glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, wvpMatrix.m[0]);

		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
		if (iTempShaderVaribleGLID != -1)
			glUniform1f(iTempShaderVaribleGLID, GLfloat(m_numFrames));

		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
		if (iTempShaderVaribleGLID != -1)
			glUniform1f(iTempShaderVaribleGLID, GLfloat(m_currentFrame));


		glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void AnimationSprite2D::Update(GLfloat deltaTime)
{
	if (m_isPlaying) {
		m_currentFrameTime += deltaTime;
		if (m_currentFrameTime >= m_frameTime) {
			m_currentFrame++;
			if (m_currentFrame >= m_numFrames) {
				m_currentFrame = 0;
			}
			m_currentFrameTime -= m_frameTime;
		}
	}
}

void AnimationSprite2D::SetPlayAnimation(bool isPlaying)
{
	m_isPlaying = isPlaying;
}

bool AnimationSprite2D::IsPlaying()
{
	return m_isPlaying;
}

void AnimationSprite2D::setFrame(int frame)
{
	if (frame <= m_numFrames) {
		m_currentFrame = frame;
		m_currentFrameTime = m_currentFrame * m_frameTime;
	}
}
