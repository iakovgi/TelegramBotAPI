#include "Types/InlineQueryResultLocation.h"

#include "Internal/ConversionFunctions.h"
#include "Types/InputMessageContent.h"

Telegram::InlineQueryResultLocation::InlineQueryResultLocation() :
	id(),
	latitude(),
	longitude(),
	title(),
	horizontal_accuracy(),
	live_period(),
	heading(),
	proximity_alert_radius(),
	reply_markup(),
	input_message_content(),
	thumb_url(),
	thumb_width(),
	thumb_height()
{}

Telegram::InlineQueryResultLocation::InlineQueryResultLocation(const QString& id,
															   const float& latitude,
															   const float& longitude,
															   const QString& title,
															   const std::optional<float>& horizontal_accuracy,
															   const std::optional<qint32>& live_period,
															   const std::optional<qint32>& heading,
															   const std::optional<qint32>& proximity_alert_radius,
															   const std::optional<InlineKeyboardMarkup>& reply_markup,
															   const std::optional<std::shared_ptr<InputMessageContent>>& input_message_content,
															   const std::optional<QString>& thumb_url,
															   const std::optional<qint32>& thumb_width,
															   const std::optional<qint32>& thumb_height) :
	id(id),
	latitude(latitude),
	longitude(longitude),
	title(title),
	horizontal_accuracy(horizontal_accuracy),
	live_period(live_period),
	heading(heading),
	proximity_alert_radius(proximity_alert_radius),
	reply_markup(reply_markup),
	input_message_content(input_message_content),
	thumb_url(thumb_url),
	thumb_width(thumb_width),
	thumb_height(thumb_height)
{}

QJsonObject Telegram::InlineQueryResultLocation::toObject() const
{
	if (isEmpty())
		return QJsonObject();

	QJsonObject inlineQueryResultLocationJsonObject{ {"type", type}, {"id", id}, {"latitude", latitude}, {"longitude", longitude}, {"title", title} };

	if (horizontal_accuracy.has_value())	inlineQueryResultLocationJsonObject.insert("horizontal_accuracy", *horizontal_accuracy);
	if (live_period.has_value())			inlineQueryResultLocationJsonObject.insert("live_period", *live_period);
	if (heading.has_value())				inlineQueryResultLocationJsonObject.insert("heading", *heading);
	if (proximity_alert_radius.has_value())	inlineQueryResultLocationJsonObject.insert("proximity_alert_radius", *proximity_alert_radius);
	if (reply_markup.has_value())			inlineQueryResultLocationJsonObject.insert("reply_markup", reply_markup->toObject());
	if (input_message_content.has_value())	inlineQueryResultLocationJsonObject.insert("input_message_content", (**input_message_content).toObject());
	if (thumb_url.has_value())				inlineQueryResultLocationJsonObject.insert("thumb_url", *thumb_url);
	if (thumb_width.has_value())			inlineQueryResultLocationJsonObject.insert("thumb_width", *thumb_width);
	if (thumb_height.has_value())			inlineQueryResultLocationJsonObject.insert("thumb_height", *thumb_height);

	return inlineQueryResultLocationJsonObject;
}

bool Telegram::InlineQueryResultLocation::isEmpty() const
{
	return id == ""
		   and latitude == 0.0
		   and longitude == 0.0
		   and title == ""
		   and horizontal_accuracy == std::nullopt
		   and live_period == std::nullopt
		   and heading == std::nullopt
		   and proximity_alert_radius == std::nullopt
		   and reply_markup == std::nullopt
		   and input_message_content == std::nullopt
		   and thumb_url == std::nullopt
		   and thumb_width == std::nullopt
		   and thumb_height == std::nullopt;
}
