<?php

namespace Tests\Feature;

use App\Models\ExerciseType;
use Tests\TestCase;

class ExerciseTypeTest extends TestCase
{
    public function test_get_all_exercise_types_returns_a_successful_response()
    {
        $response = $this->get('/api/v1/exercise-types');

        $response->assertStatus(200);
    }
    public function test_get_exercise_type_by_id_returns_a_successful_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $response = $this->get('/api/v1/exercise-types/' . $exerciseType->id);

        $data = [
            'data' => [
                'id' => $exerciseType->id,
                'name' => $exerciseType->name,
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_get_exercise_type_by_id_returns_a_bad_request_response()
    {
        $response = $this->get('/api/v1/exercise-types/f');
        $response->assertStatus(400);
    }
    public function test_get_exercise_type_by_id_returns_a_not_found_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $response = $this->get('/api/v1/exercise-types/' . $exerciseType->id + 1);
        $response->assertStatus(404);
    }

    public function test_create_exercise_type_returns_a_successful_response()
    {
        $exerciseType = ExerciseType::factory()->raw();
        $response = $this->postJson('/api/v1/exercise-types/', $exerciseType);
        $data = [
            'data' => [
                'name' => $exerciseType['name'],
            ],
        ];
        $response->assertStatus(201)->assertJson($data);
        $this->assertDatabaseHas('exercise_types', $exerciseType);
    }
    public function test_create_exercise_type_returns_a_bad_request_response()
    {
        $exerciseType = ExerciseType::factory()->raw();
        $this->postJson('/api/v1/exercise-types/', $exerciseType);

        $response = $this->postJson('/api/v1/exercise-types/', $exerciseType);
        $response->assertStatus(400);
    }

    public function test_update_exercise_type_returns_a_successful_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exerciseType->id + 1];
        $response = $this->putJson('/api/v1/exercise-types/' . $exerciseType->id, $updatedData);
        $data = [
            'data' => [
                'id' => $exerciseType->id,
                'name' => $updatedData['name'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
        $this->assertDatabaseHas('exercise_types', $updatedData);
    }
    public function test_update_exercise_type_returns_a_not_found_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $updatedData = ['name' => 'Updated Name ' . $exerciseType->id + 1];
        $response = $this->putJson('/api/v1/exercise-types/' . $exerciseType->id + 1, $updatedData);
        $response->assertStatus(404);
    }
    public function test_update_exercise_type_invalid_url_returns_a_bad_request_response()
    {
        $updatedData = ['name' => 'Updated Name'];
        $response = $this->putJson('/api/v1/exercise-types/f', $updatedData);
        $response->assertStatus(400);
    }
    public function test_update_exercise_type_not_unique_name_returns_a_bad_request_response()
    {
        $exerciseType = ExerciseType::inRandomOrder()->first();
        $newExerciseType = ExerciseType::factory()->create();
        $updatedData = ['name' => $exerciseType->name];
        $response = $this->putJson('/api/v1/exercise-types/' . $newExerciseType->id, $updatedData);
        $response->assertStatus(400);
    }

    public function test_delete_exercise_type_returns_a_successful_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $response = $this->deleteJson('/api/v1/exercise-types/' . $exerciseType->id);
        $data = [
            'data' => [
                'id' => $exerciseType['id'],
                'name' => $exerciseType['name'],
            ],
        ];
        $response->assertStatus(200)->assertJson($data);
    }
    public function test_delete_exercise_type_returns_a_not_found_response()
    {
        $exerciseType = ExerciseType::factory()->create();
        $response = $this->deleteJson('/api/v1/exercise-types/' . $exerciseType->id + 1);
        $response->assertStatus(404);
    }
    public function test_delete_exercise_type_returns_a_bad_request_response()
    {
        $response = $this->deleteJson('/api/v1/exercise-types/f');
        $response->assertStatus(400);
    }
}
