#include "Expo/Spotlight.h" // تأكد من صحة المسار
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Spotlight::Spotlight()
// 1. Housing (الجسم الخارجي): أسطوانة كبيرة مفلترة تشبه المخروط
// Radius Top=8, Bottom=6, Height=12
    : m_Housing(6.0f, 8.0f, 12.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // 2. Lens (الزجاج): دائرة بيضاء (مكعب رفيع جداً)
    m_Lens(7.5f, 7.5f, 0.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // 3. Handle (المقبض): اسطوانة صغيرة فوق اللمبة
    m_Handle(1.5f, 1.5f, 10.0f, 12, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // 4. Base (العصا الطويلة) - بقيت كما هي
    m_Base(2.0f, 2.0f, 150.0f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // 5. Stand (القاعدة الثقيلة)
    m_Stand(10.0f, 10.0f, 10.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    m_Position = { 0.0f, 0.0f, 0.0f };
    m_RotationAngle = 0.0f;
    m_RotationAxis = { 0.0f, 1.0f, 0.0f };
    m_Scale = 1.0f;
    setTextures();
}

Spotlight::~Spotlight() {}

void Spotlight::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Spotlight::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void Spotlight::setScale(float s) { m_Scale = s; }

glm::mat4 Spotlight::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void Spotlight::setTextures() {
    std::string metalTexture = "assets/textures/awesomeface.png"; // معدن للقاعدة
    std::string darkTexture = "assets/textures/car/dark_grey_metal.jpg"; // لون داكن للجسم (أسود/رمادي)
    std::string lightTexture = "assets/textures/glass.jpg"; // أبيض للزجاج

    // القاعدة
    m_Base.setSideTexture(metalTexture);
    m_Stand.setSideTexture(metalTexture);
    m_Handle.setSideTexture(metalTexture);

    // جسم اللمبة (داكن)
    m_Housing.setSideTexture(darkTexture);
    // الزجاج (أبيض ساطع)
    m_Lens.setAllFacesTexture(lightTexture);
}

void Spotlight::update(float dt) { (void)dt; }

void Spotlight::drawOpaque() {
    updateModelMatrix();
    glm::mat4 root = getModelMatrix();

    // ربط الكل
    m_Housing.setParentModel(root);
    m_Lens.setParentModel(root);
    m_Handle.setParentModel(root);
    m_Base.setParentModel(root);
    m_Stand.setParentModel(root);

    // --- رسم القاعدة ---
    // 1. القاعدة السفلية
    m_Stand.setPosition({ 0.0f, 5.0f, 0.0f });
    m_Stand.drawOpaque();

    // 2. العصا الطويلة
    m_Base.setPosition({ 0.0f, 75.0f, 0.0f });
    m_Base.drawOpaque();

    // --- رسم رأس اللمبة (Realistic Head) ---
    // نحتاج لمصفوفة مؤقتة لتدوير الرأس فقط لينظر للأسفل
    glm::mat4 headMatrix = glm::translate(root, { 0.0f, 150.0f, 0.0f }); // ننتقل لقمة العصا
    headMatrix = glm::rotate(headMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0)); // نوجه الرأس لأسفل

    // 1. الجسم الخارجي (Housing) - المخروط
    m_Housing.setParentModel(headMatrix);
    // Housing مركزه في (0,0,0) بالنسبة لـ headMatrix، وهو الآن مقلوب
    m_Housing.setPosition({ 0.0f, 0.0f, 0.0f });
    m_Housing.drawOpaque();

    // 2. الزجاج (Lens) - يوضع في مقدمة المخروط (لأنه مقلوب، المقدمة تصبح Z موجب سالب حسب الاتجاه)
    // بما أننا دورنا -90 درجة حول X، فإن المحور Z أصبح يشير لأسفل.
    // نريد الزجاج في "قمة" المخروط المقلوب.
    // ارتفاع الـ Housing هو 12. الزجاج يكون في 6.0 (نصف الارتفاع).
    m_Lens.setParentModel(headMatrix);
    m_Lens.setPosition({ 0.0f, 0.0f, 6.0f }); // يبرز قليلاً من المقدمة
    m_Lens.drawOpaque();

    // 3. المقبض (Handle) - فوق اللمبة
    m_Handle.setParentModel(headMatrix);
    m_Handle.setPosition({ 0.0f, 8.0f, 0.0f }); // فوق اللمبة
    // تدوير المقبض ليكون عرضياً
    m_Handle.setRotation(90.0f, { 0, 0, 1 });
    m_Handle.drawOpaque();
}

void Spotlight::drawTransparent() { /* فارغ */ }
void Spotlight::getTransparent() { /* فارغ */ }

void Spotlight::onImguiRender() {
    ImGui::SliderFloat3("Spotlight Position", &m_Position.x, -100, 100);
}