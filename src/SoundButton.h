#pragma once

#include <QPushButton>
#include <QList>
#include <QUrl>

class ConfigModel;

class SoundButton : public QPushButton
{
	Q_OBJECT

  public:
	SoundButton(QWidget* parent);
	virtual ~SoundButton();

	virtual void dragEnterEvent(QDragEnterEvent* evt) override;
	virtual void dragMoveEvent(QDragMoveEvent* evt) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* evt) override;
	virtual void dropEvent(QDropEvent* evt) override;
	virtual void mousePressEvent(QMouseEvent* evt) override;
	virtual void mouseReleaseEvent(QMouseEvent* evt) override;
	virtual void mouseMoveEvent(QMouseEvent* evt) override;

	void setBackgroundColor(const QColor& color);

	// Visual indication of this button's sound playback state.
	// None: normal appearance (button's configured background color, if any)
	// Playing: continuously alternates between two colors (driven by toggleBlink())
	// Paused: static, distinct color
	enum class PlayIndicator
	{
		None,
		Playing,
		Paused,
	};
	void setPlayIndicator(PlayIndicator indicator);
	// Call periodically (e.g. from a single shared QTimer) while indicator == Playing
	// to advance the blink. No-op for any other indicator state.
	void toggleBlink();

  signals:
	void fileDropped(const QList<QUrl>&);
	void buttonDropped(SoundButton* button);

  private:
	void applyBackgroundColor(const QColor& color);
	void applyPlayIndicatorColor();

	bool pressing;
	bool dragging;
	QPoint dragStart;
	QColor backgroundColor;
	PlayIndicator playIndicator;
	bool blinkPhase;
};
