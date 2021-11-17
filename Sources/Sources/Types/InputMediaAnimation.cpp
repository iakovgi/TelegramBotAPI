#include "Types/InputMediaAnimation.h"

#include "qjsonobject.h"

#include "Internal/ConversionFunctions.h"

Telegram::InputMediaAnimation::InputMediaAnimation() :
	media(),
	thumb(),
	caption(),
	parse_mode(),
	caption_entities(),
	width(),
	height(),
	duration()
{}

Telegram::InputMediaAnimation::InputMediaAnimation(const std::variant<QFile*, QString>& media,
												   const std::optional<std::variant<QFile*, QString>>& thumb,
												   const std::optional<QString>& caption,
												   const std::optional<QString>& parse_mode,
												   const std::optional<QVector<MessageEntity>>& caption_entities,
												   const std::optional<qint32>& width,
												   const std::optional<qint32>& height,
												   const std::optional<qint32>& duration) :
	media(media),
	thumb(thumb),
	caption(caption),
	parse_mode(parse_mode),
	caption_entities(caption_entities),
	width(width),
	height(height),
	duration(duration)
{}

Telegram::InputMediaAnimation::InputMediaAnimation(const QJsonObject& jsonObject)
{
	jsonObject.contains("media")			? media = jsonObject["media"].toString()															: media = nullptr;
	jsonObject.contains("thumb")			? thumb = jsonObject["thumb"].toString()															: thumb = std::nullopt;
	jsonObject.contains("caption")			? caption = jsonObject["caption"].toString()														: caption = std::nullopt;
	jsonObject.contains("parse_mode")		? parse_mode = jsonObject["parse_mode"].toString()													: parse_mode = std::nullopt;
	jsonObject.contains("caption_entities") ? caption_entities = QJsonArrayToQVector<MessageEntity>(jsonObject["caption_entities"].toArray())	: caption_entities = std::nullopt;
	jsonObject.contains("width")			? width = jsonObject["width"].toInt()																: width = std::nullopt;
	jsonObject.contains("height")			? height = jsonObject["height"].toInt()																: height = std::nullopt;
	jsonObject.contains("duration")			? duration = jsonObject["duration"].toInt()															: duration = std::nullopt;
}

QJsonObject Telegram::InputMediaAnimation::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inputMediaAnimationJsonObject{ {"type", type} };

	if (std::holds_alternative<QFile*>(media))  inputMediaAnimationJsonObject.insert("media", QString("attach://%1").arg(std::get<QFile*>(media)->fileName()));
	if (std::holds_alternative<QString>(media)) inputMediaAnimationJsonObject.insert("media", std::get<QString>(media));

	if (thumb.has_value())
	{
		if (std::holds_alternative<QFile*>(*thumb))  inputMediaAnimationJsonObject.insert("thumb", QString("attach://%1").arg(std::get<QFile*>(*thumb)->fileName()));
		if (std::holds_alternative<QString>(*thumb)) inputMediaAnimationJsonObject.insert("thumb", std::get<QString>(*thumb));
	}

	if (caption.has_value())			inputMediaAnimationJsonObject.insert("caption", *caption);
	if (parse_mode.has_value())			inputMediaAnimationJsonObject.insert("parse_mode", *parse_mode);
	if (caption_entities.has_value())	inputMediaAnimationJsonObject.insert("caption_entities", QVectorToQJsonArray(*caption_entities));
	if (width.has_value())				inputMediaAnimationJsonObject.insert("width", *width);
	if (height.has_value())				inputMediaAnimationJsonObject.insert("height", *height);

	return inputMediaAnimationJsonObject;
}

bool Telegram::InputMediaAnimation::isEmpty() const
{
	/* Check if std::variant<QFile*, QString> media contains any value */
	bool holdsMedia(false);
	if (std::holds_alternative<QFile*>(media))
		if (std::get<QFile*>(media) != nullptr) holdsMedia = true;
	if (std::holds_alternative<QString>(media))
		if (std::get<QString>(media) != "") holdsMedia = true;

	return holdsMedia == false
		   and thumb == std::nullopt
		   and caption == std::nullopt
		   and parse_mode == std::nullopt
		   and caption_entities == std::nullopt
		   and width == std::nullopt
		   and height == std::nullopt
		   and duration == std::nullopt;
}
